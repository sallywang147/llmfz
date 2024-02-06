#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pffft.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pffft_init();
    initialized = true;
  }

  // Call pffft_simd_size() with a random number of points.
  FuzzedDataProvider provider(data, size);
  const size_t num_points = provider.ConsumeIntegralInRange<size_t>(1, 1000000);

  // Ensure that the number of points is a power of two.
  const size_t num_points_rounded = 1 << static_cast<size_t>(std::ceil(std::log2(num_points)));

  // Call pffft_simd_size() with the rounded number of points.
  const int simd_size = pffft_simd_size(num_points_rounded);

  // Ensure that the SIMD size is a power of two.
  const int simd_size_rounded = 1 << static_cast<int>(std::ceil(std::log2(simd_size)));

  // Ensure that the SIMD size is a multiple of the number of points.
  const int num_simd_groups = num_points_rounded / simd_size_rounded;
  if (num_simd_groups * simd_size_rounded != num_points_rounded) {
    abort();
  }

  return 0;
}