 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const uint8_t* next_in = data;
  size_t avail_in = size;

  const int kBufferSize = 1024;
  uint8_t* buffer = (uint8_t*) malloc(kBufferSize);
  if (!buffer) {
    // OOM is out-of-scope here.
    return 0;
  }
  /* The biggest "magic number" in brotli is 16MiB - 16, so no need to check
     the cases with much longer output. */
  const size_t total_out_limit = (1 << 26);
  size_t total_out = 0;

  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;
  while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
    size_t avail_out = kBufferSize;
    uint8_t* next_out = buffer;
    result = BrotliDecoderDecompress(avail_in, next_in, &avail_out, next_out);
    if (total_out > total_out_limit)
      break;
  }

  free(buffer);
  return 0;
}