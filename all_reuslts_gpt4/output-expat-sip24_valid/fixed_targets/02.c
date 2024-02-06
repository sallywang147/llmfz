#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Since the function sip24_valid() does not take any arguments, we do not need to use FuzzedDataProvider in this case.
  // Just call the function.
  sip24_valid();

  return 0;
}