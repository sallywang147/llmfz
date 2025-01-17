 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1)
    return 0;
  BrotliBitReader br;
  BrotliInitBitReader(&br, data, size);
  size_t pos = 0;
  while (pos < size) {
    BrotliSafeReadBits32Slow(&br, 1, &pos);
  }
  return 0;
}