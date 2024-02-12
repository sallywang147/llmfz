#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <brotli/decode.h>
}

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1)
    return 0;
  const uint8_t* next_in = data;
  size_t avail_in = size;

  const int kBufferSize = 1024;
  uint8_t* buffer = (uint8_t*) malloc(kBufferSize);
  if (!buffer) {
    // OOM is out-of-scope here.
    return 0;
  }
  size_t total_out = 0;

  BrotliDecoderState* state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    free(buffer);
    return 0;
  }

  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;
  while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
    size_t avail_out = kBufferSize;
    uint8_t* next_out = buffer;
    result = BrotliDecoderDecompressStream(
        state, &avail_in, &next_in, &avail_out, &next_out, &total_out);
    if (total_out > 1 << 26)
      break;
  }

  if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
    BrotliDecoderAttachDictionary(state, 0, size, (char*)data);
    result = BrotliDecoderDecompressStream(
        state, &avail_in, &next_in, &avail_out, &next_out, &total_out);
  }

  BrotliDecoderDestroyInstance(state);
  free(buffer);
  return 0;
}