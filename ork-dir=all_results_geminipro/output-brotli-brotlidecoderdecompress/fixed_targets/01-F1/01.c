#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize variables.
  size_t available_in = size;
  const uint8_t *next_in = data;
  size_t available_out = 1024;
  char *next_out = (char *)malloc(available_out);
  size_t total_out = 0;

  // Create a Brotli decoder state.
  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    free(next_out);
    return 0;
  }

  // Decompress the input data.
  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;
  while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
    // Check if we need to allocate more space for the output buffer.
    if (total_out + available_out > 1 << 26) {
      available_out *= 2;
      next_out = (char *)realloc(next_out, available_out);
    }

    // Decompress the next chunk of data.
    result = BrotliDecoderDecompressStream(state, &available_in, &next_in, &available_out, &next_out, &total_out);
  }

  // Clean up.
  BrotliDecoderDestroyInstance(state);
  free(next_out);

  return 0;
}
```

The build issue is caused by the missing `extern "C"` wrapper around the `#include <brotli/decode.h>` directive. This is necessary because the Brotli library is written in C and uses the C calling convention, while the LibFuzzer entry point is written in C++ and uses the C++ calling convention. By wrapping the `#include` directive with `extern "C"`, we tell the compiler to use the C calling convention for the Brotli functions, which allows them to be called from the C++ code.