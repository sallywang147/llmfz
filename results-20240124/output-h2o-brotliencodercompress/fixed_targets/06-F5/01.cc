#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>

#include "fuzzer/FuzzedDataProvider.h"
#include "brotli/encode.h"

extern "C" {
#include "brotli/decode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Pick a random quality level.
  const int quality = stream.ConsumeIntegral<int>() % 12;

  // Pick a random window size.
  const int lgwin = stream.ConsumeIntegral<int>() % 24;

  // Pick a random block size.
  const int block_size = stream.ConsumeIntegral<int>() % 256;

  // Pick a random input size.
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);

  // Generate random input data.
  std::string input = stream.ConsumeBytesAsString(input_size);

  // Allocate a buffer for the compressed data.
  size_t compressed_size = BrotliEncoderMaxCompressedSize(input_size);
  std::string compressed(compressed_size, '\0');

  // Compress the input data.
  BrotliEncoderCompressStream(quality, lgwin, block_size, input_size, input.data(),
                       &compressed_size, compressed.data());

  // Decompress the compressed data.
  std::string decompressed(input_size, '\0');
  BrotliDecoderResult result = BrotliDecoderDecompressStream(compressed_size, compressed.data(), &input_size,
                         decompressed.data(), nullptr, nullptr);

  // Check that the decompressed data is the same as the original input data.
  if (result != BROTLI_DECODER_RESULT_SUCCESS || input != decompressed) {
    abort();
  }

  return 0;
}