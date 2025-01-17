#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }

  while (stream.remaining_bytes() > 0) {
    size_t avail_in = stream.ConsumeIntegralInRange<size_t>(0, size);
    const uint8_t *next_in = data;

    BrotliDecoderResult result = BrotliDecoderDecompressStream(state, &avail_in, &next_in, nullptr, nullptr, nullptr);
    if (result == BROTLI_DECODER_RESULT_ERROR) {
      break;
    }
  }

  BrotliDecoderIsFinished(state);

  BrotliDecoderDestroyInstance(state);
  return 0;
}