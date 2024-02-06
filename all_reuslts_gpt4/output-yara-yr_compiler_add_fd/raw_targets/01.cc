#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "yara.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    yr_initialize();
    initialized = true;
  }

  YR_COMPILER* compiler = NULL;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  std::string namespace_ = provider.ConsumeRandomLengthString();
  std::string file_name = provider.ConsumeRandomLengthString();

  // Create a temporary file and write the data to it.
  FILE* file = tmpfile();
  if (!file) {
    yr_compiler_destroy(compiler);
    return 0;
  }

  std::vector<uint8_t> buffer = provider.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), file);
  rewind(file);

  int rules_fd = fileno(file);
  yr_compiler_add_fd(compiler, rules_fd, const_cast<char*>(namespace_.c_str()), const_cast<char*>(file_name.c_str()));

  fclose(file);
  yr_compiler_destroy(compiler);

  return 0;
}