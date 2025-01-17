#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "mail_params.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function mail_params_init() does not take any arguments, we do not need
  // to use FuzzedDataProvider in this case. Just call the function.
  mail_params_init();
  return 0;
}