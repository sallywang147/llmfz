#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  const uint8_t *next_in = data;
  size_t avail_in = size;
  BrotliBitReader br;
  BrotliBitReaderInit(&br, next_in, avail_in);
  size_t val;
  BrotliSafeReadBits32Slow(&br, 32, &val);
  return 0;
}