#include <stddef.h>
#include <stdint.h>
#include <yara.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern "C" {
#include <yara/libyara.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int fd = open("/dev/null", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd < 0)
    return 0;

  YR_COMPILER *compiler = NULL;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    close(fd);
    return 0;
  }

  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);

  yr_lex_parse_rules_fd(fd, compiler, YR_RULES_MEM_DF);

  close(fd);
  yr_compiler_destroy(compiler);

  return 0;
}