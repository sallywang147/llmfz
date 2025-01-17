#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t encoded_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string encoded = stream.ConsumeBytesAsString(encoded_size);
  size_t decoded_size = stream.remaining_bytes();

  // Allocate memory for the decoded data
  char* decoded = (char*)malloc(decoded_size);
  if (!decoded) {
    // OOM is out-of-scope here.
    return 0;
  }

  BrotliDecoderDecompress(encoded_size, encoded.c_str(), &decoded_size, decoded);

  free(decoded);
  return 0;
}