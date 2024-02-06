#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int kBufferSize = 1024;
  uint8_t *buffer = (uint8_t *)malloc(kBufferSize);
  if (!buffer) {
    // OOM is out-of-scope here.
    return 0;
  }

  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    free(buffer);
    return 0;
  }

  size_t total_out = 0;

  while (stream.remaining_bytes() > 0) {
    size_t avail_in = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    const uint8_t *next_in = stream.ConsumeBytes<uint8_t>(avail_in).data();
    BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;
    while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
      size_t avail_out = kBufferSize;
      uint8_t *next_out = buffer;
      result = BrotliDecoderDecompressStream(state, &avail_in, &next_in, &avail_out, &next_out, &total_out);
      if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
        size_t output_size = 0;
        char* output = BrotliDecoderTakeOutput(state, &output_size);
        // Do something with output, e.g., check its validity
      }
    }
    if (result != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT)
      break;
  }

  BrotliDecoderDestroyInstance(state);
  free(buffer);
  return 0;
}