#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Since the function doesn't have any parameters, we don't need to use the FuzzedDataProvider.
  // Just call the function.
  validate_pffft_simd();

  return 0;
}