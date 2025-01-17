#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int TPM12_MainInit();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function TPM12_MainInit() does not take any arguments, we don't need to use the FuzzedDataProvider in this case.
  TPM12_MainInit();
  return 0;
}