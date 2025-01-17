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

  FuzzedDataProvider provider(data, size);

  const size_t fft_size = provider.ConsumeIntegralInRange<size_t>(
      1, 1 << 20);
  const size_t number_of_bytes = fft_size * sizeof(float);

  std::vector<float> input_buffer(fft_size);
  std::vector<float> output_buffer(fft_size);

  provider.ConsumeFloatArray(input_buffer.data(), input_buffer.size());

  pffft_transform_ordered(input_buffer.data(), output_buffer.data(), nullptr,
                          PFFFT_FORWARD);
  pffft_transform_ordered(output_buffer.data(), input_buffer.data(), nullptr,
                          PFFFT_BACKWARD);

  validate_pffft_simd();

  return 0;
}