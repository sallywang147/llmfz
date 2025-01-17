#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Wrap Brotli header with extern "C" {} to fix the build error.
extern "C" {
#include <brotli/decode.h>
}

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  BrotliBitReader br;
  if (BrotliCreateBitReader(&br, data, size) != BROTLI_TRUE) {
    // OOM is out-of-scope here.
    return 0;
  }

  size_t bit_pos = 0;
  size_t bits_read = 0;
  while (BrotliSafeReadBits32Slow(&br, 1, &bits_read) == BROTLI_TRUE)
    bit_pos++;

  BrotliDestroyBitReader(&br);
  return 0;
}