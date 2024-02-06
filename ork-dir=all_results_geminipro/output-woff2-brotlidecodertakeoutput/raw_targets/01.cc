#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  BrotliDecoderState *s = BrotliDecoderCreateInstance(0, 0, 0);
  if (!s) return 0;
  FuzzedDataProvider stream(data, size);
  BrotliDecoderSetParameter(s, BROTLI_DECODER_PARAM_LARGE_WINDOW, 1);
  size_t available_in = stream.remaining_bytes();
  const uint8_t *next_in = stream.ConsumeBytes<uint8_t>(available_in).data();
  size_t total_out = 0;
  while (BrotliDecoderHasMoreOutput(s)) {
    size_t available_out = 65536;
    uint8_t *next_out = new uint8_t[available_out];
    BrotliDecoderResult result = BrotliDecoderDecompressStream(
        s, &available_in, &next_in, &available_out, &next_out, &total_out);
    delete[] next_out;
    if (result != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) break;
    available_in = stream.remaining_bytes();
    next_in = stream.ConsumeBytes<uint8_t>(available_in).data();
  }
  BrotliDecoderDestroyInstance(s);
  return 0;
}