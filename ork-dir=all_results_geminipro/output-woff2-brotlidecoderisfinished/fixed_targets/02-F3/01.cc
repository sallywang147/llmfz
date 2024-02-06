#include <fuzzer/FuzzedDataProvider.h>
#include <brotli/decode.h>

extern "C" {
#include <brotli/decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  BrotliDecoderState* state = BrotliDecoderCreateInstance(nullptr, nullptr, nullptr);
  if (state == nullptr) {
    return 0;
  }
  while (stream.remaining_bytes() > 0) {
    size_t consumed;
    BrotliDecoderResult result = BrotliDecoderDecompressStream(
        state, &stream.ConsumeRemainingBytes(), &consumed, nullptr);
    if (result != BROTLI_DECODER_RESULT_SUCCESS &&
        result != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
      BrotliDecoderDestroyInstance(state);
      return 0;
    }
    if (BrotliDecoderIsFinished(state)) {
      BrotliDecoderDestroyInstance(state);
      return 0;
    }
  }
  BrotliDecoderDestroyInstance(state);
  return 0;
}