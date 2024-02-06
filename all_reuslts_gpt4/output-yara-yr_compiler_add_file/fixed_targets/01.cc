#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "yara/compiler.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  YR_COMPILER* compiler = nullptr;
  if (yr_compiler_create(&compiler) != ERROR_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // We need at least one byte for each parameter.
  if (provider.remaining_bytes() < 3) {
    yr_compiler_destroy(compiler);
    return 0;
  }

  // Use the first byte to determine the size of the namespace string.
  size_t namespace_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes() / 3);
  std::string namespace_ = provider.ConsumeBytesAsString(namespace_size);

  // Use the next byte to determine the size of the file name string.
  size_t file_name_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes() / 2);
  std::string file_name = provider.ConsumeBytesAsString(file_name_size);

  // Use the remaining bytes for the rules file.
  std::string rules = provider.ConsumeRemainingBytesAsString();
  FILE* rules_file = fmemopen((void*)rules.data(), rules.size(), "r");
  if (rules_file == nullptr) {
    yr_compiler_destroy(compiler);
    return 0;
  }

  yr_compiler_add_file(compiler, rules_file, namespace_.c_str(), file_name.c_str());

  fclose(rules_file);
  yr_compiler_destroy(compiler);

  return 0;
}