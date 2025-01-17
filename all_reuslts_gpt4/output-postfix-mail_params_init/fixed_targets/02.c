#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function mail_params_init() does not have any parameters, we don't need to use FuzzedDataProvider.
  // We just call the function directly.
  mail_params_init();

  return 0;
}