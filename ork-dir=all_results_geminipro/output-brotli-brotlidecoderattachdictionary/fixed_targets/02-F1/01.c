#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <brotli/decode.h>
}

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }

  size_t dictionary_size = size;
  if (size > 0)
    dictionary_size = data[size - 1] & 7;
  if (dictionary_size > 0) {
    BrotliDecoderAttachDictionary(state, 0, dictionary_size, (char *)data);
  }

  BrotliDecoderDestroyInstance(state);
  return 0;
}