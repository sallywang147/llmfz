#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "ixheaacd_hbe_apply_ifft_336.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t output_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const int channel_count = stream.ConsumeIntegralInRange<int>(1, 10);
  const int window_size = stream.ConsumeIntegralInRange<int>(1, 10);

  std::vector<float> input_buffer(input_length);
  std::vector<float> output_buffer(output_length);

  stream.ConsumeFloatingPointArray<float>(input_buffer.data(), input_length);
  ixheaacd_hbe_apply_ifft_336(input_buffer.data(), output_buffer.data(),
                             channel_count, window_size);

  return 0;
}