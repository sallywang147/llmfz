#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  BrotliBitReader reader;
  BrotliInitBitReader(&reader, data, size);

  size_t num_bits = 0;
  while (BrotliSafeReadBits32Slow(&reader, 1, &num_bits) == 0) {
    // Do nothing.
  }

  return 0;
}