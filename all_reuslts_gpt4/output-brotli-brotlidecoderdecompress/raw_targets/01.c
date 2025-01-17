#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t encodedSize = stream.ConsumeIntegral<size_t>();
  std::string encodedData = stream.ConsumeRemainingBytesAsString();
  char *encodedBuffer = const_cast<char *>(encodedData.c_str());

  size_t decodedSize = 0;
  char *decodedBuffer = nullptr;

  BrotliDecoderDecompress(encodedSize, encodedBuffer, &decodedSize, decodedBuffer);

  return 0;
}