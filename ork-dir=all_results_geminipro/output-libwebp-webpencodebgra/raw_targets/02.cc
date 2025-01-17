#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int width = stream.ConsumeIntegralInRange<int>(1, 10000);
  const int height = stream.ConsumeIntegralInRange<int>(1, 10000);
  const int bits_per_sample = stream.ConsumeIntegralInRange<int>(1, 4);
  const float quality = stream.ConsumeFloatingPointInRange<float>(0.0, 100.0);

  std::vector<uint8_t> input_buffer(width * height * bits_per_sample);
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), input_buffer.size());

  size_t output_size = 0;
  char* output_buffer = nullptr;
  WebPEncodeBGRA(reinterpret_cast<char*>(input_buffer.data()), width, height,
                 bits_per_sample, quality, &output_buffer, &output_size);
  free(output_buffer);

  return 0;
}