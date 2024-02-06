#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "pffft.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a FuzzedDataProvider instance.
  FuzzedDataProvider stream(data, size);

  // Call the function under test.
  int simd_size = pffft_simd_size();

  return 0;
}