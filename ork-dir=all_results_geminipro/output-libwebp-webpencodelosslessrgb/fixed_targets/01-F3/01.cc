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
  const uint8_t width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t height = stream.ConsumeIntegral<uint8_t>();
  const uint8_t bits_per_sample = stream.ConsumeIntegral<uint8_t>();
  const std::vector<uint8_t> input_buffer = stream.ConsumeBytes<uint8_t>(
      width * height * bits_per_sample / 8);

  char* output_buffer = nullptr;
  size_t output_size = WebPEncodeLosslessRGB(
      reinterpret_cast<char*>(input_buffer.data()), width, height, bits_per_sample,
      &output_buffer);
  if (output_buffer != nullptr) {
    free(output_buffer);
  }

  return 0;
}