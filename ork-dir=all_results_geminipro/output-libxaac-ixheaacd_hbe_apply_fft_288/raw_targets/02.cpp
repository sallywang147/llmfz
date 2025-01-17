#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_samples = stream.ConsumeIntegralInRange<size_t>(1, 288);
  std::vector<float> input_samples(num_samples);
  std::vector<float> output_samples(num_samples);
  stream.ConsumeFloatingPointArray<float>(input_samples.data(), num_samples);
  ixheaacd_hbe_apply_fft_288(input_samples.data(), output_samples.data(),
                             num_samples, 0);
  return 0;
}