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
  const int width = stream.ConsumeIntegral<int>();
  const int height = stream.ConsumeIntegral<int>();
  const int bits_per_sample = stream.ConsumeIntegral<int>();
  const std::vector<uint8_t> input = stream.ConsumeBytes<uint8_t>(
      width * height * bits_per_sample / 8);
  char* output = nullptr;
  size_t output_size = WebPEncodeLosslessBGR(
      reinterpret_cast<char*>(input.data()), width, height, bits_per_sample,
      &output);
  free(output);
  return 0;
}