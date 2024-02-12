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

  size_t total_out = 0;

  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;
  while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
    size_t avail_out = kBufferSize;
    uint8_t* next_out = buffer;
    result = BrotliDecoderDecompress(avail_in, next_in, &avail_out, next_out);
    if (result != BROTLI_DECODER_RESULT_SUCCESS)
      break;
    total_out += avail_out;
  }

  free(buffer);
  return 0;
}