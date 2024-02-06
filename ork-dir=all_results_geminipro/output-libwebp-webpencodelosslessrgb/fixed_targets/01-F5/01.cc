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

  size_t output_size = 0;
  uint8_t* output_buffer =
      static_cast<uint8_t*>(malloc(output_size));  // Allocate memory for output
  if (output_buffer == nullptr) {
    return 0;  // Return early if memory allocation fails
  }
  WebPEncodeLosslessRGB(reinterpret_cast<char*>(input_buffer.data()), width, height,
                        bits_per_sample, &output_size, output_buffer);
  free(output_buffer);  // Free the allocated memory

  return 0;
}