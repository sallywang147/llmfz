#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "brotli/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);

  int quality = stream.ConsumeIntegralInRange<int>(BROTLI_MIN_QUALITY, BROTLI_MAX_QUALITY);
  int lgwin = stream.ConsumeIntegralInRange<int>(BROTLI_MIN_WINDOW_BITS, BROTLI_MAX_WINDOW_BITS);
  int mode = stream.ConsumeIntegralInRange<int>(BROTLI_MODE_GENERIC, BROTLI_MODE_TEXT);

  size_t input_size = stream.remaining_bytes() / 2;
  std::string input = stream.ConsumeBytesAsString(input_size);
  size_t encoded_size = size - input_size;
  std::vector<char> encoded(encoded_size);

  BrotliEncoderCompress(quality, lgwin, mode, input.size(), input.data(), &encoded_size, encoded.data());

  return 0;
}