#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "or.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string config_file = stream.ConsumeRemainingBytesAsString();
  struct or_options_t *old_options = options_new();
  if (old_options == nullptr) {
    return 0;
  }
  const int ret = options_act__real(old_options);
  options_free(old_options);
  return ret;
}