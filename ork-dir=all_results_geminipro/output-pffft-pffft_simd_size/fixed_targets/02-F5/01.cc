#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "pffft.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  (void)data;
  (void)size;

  // Call pffft_simd_size() to maximize code coverage.
  pffft_simd_size();

  return 0;
}