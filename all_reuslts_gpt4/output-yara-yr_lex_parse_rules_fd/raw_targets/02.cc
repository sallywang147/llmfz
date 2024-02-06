#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <fcntl.h>

#include "yara.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    yr_initialize();
    initialized = true;
  }

  YR_COMPILER* compiler = nullptr;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    return 0;
  }

  // Create a temporary file and write the data into it.
  char filename[] = "/tmp/fuzz-yr_lex_parse_rules_fd-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    yr_compiler_destroy(compiler);
    return 0;
  }
  unlink(filename);
  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);

  yr_lex_parse_rules_fd(fd, compiler);

  close(fd);
  yr_compiler_destroy(compiler);

  return 0;
}