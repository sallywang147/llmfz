#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "libyr.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _YR_COMPILER* compiler = yr_compiler_new();
  if (compiler == nullptr) {
    return 0;
  }

  const size_t rules_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::string rules_data = stream.ConsumeBytesAsString(rules_size);
  const std::string namespace_ = stream.ConsumeRemainingBytesAsString();

  yr_compiler_add_bytes(compiler,
                        const_cast<char*>(rules_data.c_str()),
                        rules_size,
                        const_cast<char*>(namespace_.c_str()));

  yr_compiler_delete(compiler);
  return 0;
}