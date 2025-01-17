#include <fuzzer/FuzzedDataProvider.h>
#include <yara.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    yr_initialize();
    initialized = true;
  }

  // Create a temporary file and write the data into it.
  char filename[] = "/tmp/fuzz-yr_lex_parse_rules_fd-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);

  // Create a YARA compiler.
  YR_COMPILER* compiler = nullptr;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    close(fd);
    unlink(filename);
    return 0;
  }

  // Parse the rules in the temporary file.
  yr_lex_parse_rules_fd(fd, compiler);

  // Clean up.
  close(fd);
  unlink(filename);
  yr_compiler_destroy(compiler);

  return 0;
}