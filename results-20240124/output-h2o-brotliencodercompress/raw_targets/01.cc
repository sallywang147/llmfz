 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "brotli/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Create a Brotli encoder instance.
  BrotliEncoderState* encoder = BrotliEncoderCreateInstance(nullptr, nullptr, nullptr);
  if (encoder == nullptr) {
    return 0;
  }

  // Set the compression level.
  BrotliEncoderSetParameter(encoder, BROTLI_PARAM_QUALITY, 11);

  // Set the input data.
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> input = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));

  // Set the output buffer.
  std::vector<uint8_t> output(BrotliEncoderGetMaxCompressedSize(input.size()));

  // Compress the data.
  size_t output_size = 0;
  int result = BrotliEncoderCompress(encoder, input.size(), input.data(), &output_size, output.data());

  // Destroy the encoder instance.
  BrotliEncoderDestroyInstance(encoder);

  return 0;
}