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

  YR_COMPILER* compiler = nullptr;
  int result = yr_compiler_create(&compiler);
  if (result != ERROR_SUCCESS || compiler == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  
  // Consume some bytes for rules_data
  size_t rules_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string rules_data = provider.ConsumeBytesAsString(rules_size);

  // Consume remaining bytes for namespace_
  std::string namespace_ = provider.ConsumeRemainingBytesAsString();

  yr_compiler_add_bytes(compiler, rules_data.c_str(), rules_size, namespace_.c_str());

  yr_compiler_destroy(compiler);

  return 0;
}