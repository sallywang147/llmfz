#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "webp/encode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint32_t width = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  const uint32_t height = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  const uint32_t bits_per_sample = stream.ConsumeIntegralInRange<uint32_t>(1, 32);
  const float quality = stream.ConsumeFloatingPoint<float>();
  const std::vector<uint8_t> input_buffer = stream.ConsumeBytes<uint8_t>(
      width * height * bits_per_sample / 8);

  size_t output_size = 0;
  WebPEncodeBGRA(reinterpret_cast<char*>(input_buffer.data()), width, height,
                 bits_per_sample, quality, &output_size);

  char* output_buffer = static_cast<char*>(malloc(output_size));
  WebPEncodeBGRA(reinterpret_cast<char*>(input_buffer.data()), width, height,
                 bits_per_sample, quality, &output_buffer);

  free(output_buffer);

  return 0;
}