#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include "yara/compiler.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    if (yr_initialize() != ERROR_SUCCESS) {
      return 0;
    }
    initialized = true;
  }

  YR_COMPILER* compiler = nullptr;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume data for namespace and file_name
  std::string namespace_ = stream.ConsumeRandomLengthString();
  std::string file_name = stream.ConsumeRandomLengthString();

  // Create a temporary file and write the remaining data into it
  char file_template[] = "/tmp/fuzz-XXXXXX";
  int rules_fd = mkstemp(file_template);
  if (rules_fd == -1) {
    yr_compiler_destroy(compiler);
    return 0;
  }

  std::vector<uint8_t> remaining_data = stream.ConsumeRemainingBytes<uint8_t>();
  write(rules_fd, remaining_data.data(), remaining_data.size());
  lseek(rules_fd, 0, SEEK_SET);

  // Call the target function
  yr_compiler_add_fd(compiler, rules_fd, const_cast<char*>(namespace_.c_str()), const_cast<char*>(file_name.c_str()));

  close(rules_fd);
  remove(file_template);
  yr_compiler_destroy(compiler);

  return 0;
}