#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the Brotli decoder state.
  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }
  
  // Call the function to fuzz.
  int is_finished = BrotliDecoderIsFinished(state);
  
  // Clean up.
  BrotliDecoderDestroyInstance(state);
  
  return 0;
}