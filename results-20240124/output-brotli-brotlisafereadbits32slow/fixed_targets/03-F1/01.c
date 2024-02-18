#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

extern "C" {
#include <brotli/types.h>
}

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  size_t addend = 0;
  if (size > 0)
    addend = data[size - 1] & 7;
  const uint8_t* next_in = data;

  BrotliBitReader* br = BrotliCreateBitReader(next_in, size);
  if (!br) {
    // OOM is out-of-scope here.
    return 0;
  }

  /* The biggest "magic number" in brotli is 16MiB - 16, so no need to check
     the cases with much longer output. */
  const size_t total_out_limit = (addend == 0) ? (1 << 26) : (1 << 24);
  size_t total_out = 0;

  if (addend == 0)
    addend = size;
  /* Test both fast (addend == size) and slow (addend <= 7) decoding paths. */
  for (size_t i = 0; i < size;) {
    size_t next_i = i + addend;
    if (next_i > size)
      next_i = size;
    size_t avail_in = next_i - i;
    i = next_i;
    size_t value = 0;
    size_t bits = 0;
    int result = BrotliSafeReadBits32Slow(br, avail_in, &bits, &value);
    if (result != BROTLI_DECODER_RESULT_SUCCESS)
      break;
    if (total_out > total_out_limit)
      break;
  }

  BrotliDestroyBitReader(br);
  return 0;
}