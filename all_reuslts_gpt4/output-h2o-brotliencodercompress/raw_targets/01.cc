#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "brotli/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int quality = stream.ConsumeIntegralInRange<int>(0, 11);
  int lgwin = stream.ConsumeIntegralInRange<int>(10, 24);
  int mode = stream.ConsumeIntegralInRange<int>(0, 2);

  size_t input_size = stream.remaining_bytes() / 2;
  std::string input = stream.ConsumeBytesAsString(input_size);
  size_t output_size = input_size * 2;  // Just a guess, should be enough.
  std::vector<char> output(output_size);

  size_t encoded_size = output_size;

  BrotliEncoderCompress(quality, lgwin, mode, input_size, input.data(), &encoded_size, output.data());

  return 0;
}