#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "TPM12.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function TPM12_MainInit() does not take any parameters, we don't need to use FuzzedDataProvider in this case.
  TPM12_MainInit();

  return 0;
}