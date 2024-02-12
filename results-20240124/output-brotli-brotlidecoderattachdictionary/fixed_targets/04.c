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
  BrotliDecoderAttachDictionary(state, 0, size, (char*) data);
  BrotliDecoderDestroyInstance(state);
  return 0;
}