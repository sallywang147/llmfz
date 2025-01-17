 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2)
    return 0;
  BrotliBitReader* br = BrotliCreateBitReader(data, size);
  if (!br) {
    // OOM is out-of-scope here.
    return 0;
  }

  size_t num_bits;
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  BrotliSafeReadBits32Slow(br, 31, &num_bits);
  B