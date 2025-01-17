#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

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

  FuzzedDataProvider stream(data, size);

  size_t rules_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes() / 2);
  std::string rules_data = stream.ConsumeBytesAsString(rules_size);
  std::string namespace_ = stream.ConsumeRemainingBytesAsString();

  yr_compiler_add_bytes(compiler, const_cast<char*>(rules_data.c_str()), rules_data.size(), const_cast<char*>(namespace_.c_str()));

  yr_compiler_destroy(compiler);

  return 0;
}