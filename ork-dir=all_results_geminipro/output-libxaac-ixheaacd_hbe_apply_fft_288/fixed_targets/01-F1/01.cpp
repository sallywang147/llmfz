#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "ixheaacd_hbe_apply_fft_288.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_samples = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t num_channels = stream.ConsumeIntegralInRange<size_t>(0, 8);
  std::vector<float> input_buffer(num_samples * num_channels);
  std::vector<float> output_buffer(num_samples * num_channels);
  stream.ConsumeFloatingPointArray<float>(input_buffer.data(),
                                        input_buffer.size());
  ixheaacd_hbe_apply_fft_288(input_buffer.data(), output_buffer.data(),
                             num_samples, num_channels);
  return 0;
}