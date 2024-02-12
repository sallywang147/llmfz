 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Brotli encoder.
  int quality = stream.ConsumeIntegralInRange<int>(0, 11);
  int lgwin = stream.ConsumeIntegralInRange<int>(10, 24);
  int lgblock = stream.ConsumeIntegralInRange<int>(0, 24);
  size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 24);
  size_t output_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 24);
  char* input_buffer = new char[input_size];
  stream.ConsumeBytes<char>(input_buffer, input_size);
  char* output_buffer = new char[output_size];

  // Compress the input data.
  int result = BrotliEncoderCompress(quality, lgwin, lgblock, input_size, input_buffer, &output_size, output_buffer);

  // Check the compression result.
  if (result != BROTLI_RESULT_SUCCESS) {
    return 0;
  }

  // Decompress the compressed data.
  size_t decompressed_size = input_size;
  char* decompressed_buffer = new char[decompressed_size];
  result = BrotliDecoderDecompress(output_size, output_buffer, &decompressed_size, decompressed_buffer);

  // Check the decompression result.
  if (result != BROTLI_RESULT_SUCCESS) {
    return 0;
  }

  // Compare the original and decompressed data.
  if (memcmp(input_buffer, decompressed_buffer, input_size) != 0) {
    return 0;
  }

  // Clean up.
  delete[] input_buffer;
  delete[] output_buffer;
  delete[] decompressed_buffer;

  return 0;
}