#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t addend = 0;
  if (size > 0)
    addend = data[size - 1] & 7;
  const uint8_t *next_in = data;

  const int kBufferSize = 1024;
  uint8_t *buffer = (uint8_t *)malloc(kBufferSize);
  if (!buffer) {
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
    int result = BrotliDecoderDecompressStream(
        (BrotliDecoderState *)NULL, &avail_in, (const char *)next_in, &avail_in,
        (char *)buffer, kBufferSize, &total_out);
    if (result != 0)
      break;
    if (total_out > total_out_limit)
      break;
    if (result != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT)
      break;
    next_in += avail_in;
  }

  free(buffer);
  return 0;
}