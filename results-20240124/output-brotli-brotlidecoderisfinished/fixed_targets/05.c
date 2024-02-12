 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  BrotliDecoderState* state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }

  const uint8_t* next_in = data;
  size_t avail_in = size;
  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;
  while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
    size_t avail_out = 1024;
    uint8_t* next_out = (uint8_t*) malloc(avail_out);
    if (!next_out) {
      // OOM is out-of-scope here.
      BrotliDecoderDestroyInstance(state);
      return 0;
    }
    result = BrotliDecoderDecompressStream(
        state, &avail_in, &next_in, &avail_out, &next_out, &avail_out);
    free(next_out);
  }

  int is_finished = BrotliDecoderIsFinished(state);

  BrotliDecoderDestroyInstance(state);
  return is_finished;
}