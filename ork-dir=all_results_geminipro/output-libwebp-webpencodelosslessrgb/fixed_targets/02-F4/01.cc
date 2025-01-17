#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "webp/encode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int width = stream.ConsumeIntegralInRange<int>(1, 10000);
  const int height = stream.ConsumeIntegralInRange<int>(1, 10000);
  const int bits_per_sample = stream.ConsumeIntegralInRange<int>(1, 32);
  const std::vector<uint8_t> input_buffer =
      stream.ConsumeBytes<uint8_t>(width * height * bits_per_sample / 8);
  uint8_t* output_buffer = nullptr;
  size_t output_size = 0;
  const size_t ret = WebPEncodeLosslessRGB(
      reinterpret_cast<const uint8_t*>(input_buffer.data()), width, height,
      bits_per_sample, &output_buffer, &output_size);
  if (ret > 0) {
    WebPFree(output_buffer);
  }
  return 0;
}