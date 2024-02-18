#include <fuzzer/FuzzedDataProvider.h>
#include <brotli/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BrotliDecoderState *s = BrotliDecoderCreateInstance(nullptr, nullptr, nullptr);
  if (s == nullptr) return 0;

  int ret;
  size_t available_in = stream.remaining_bytes();
  const uint8_t *next_in = stream.ConsumeBytes<uint8_t>(available_in).data();
  size_t total_out = 0;
  while (available_in > 0) {
    ret = BrotliDecoderDecompressStream(s, &available_in, &next_in, &total_out,
                                       nullptr, nullptr);
    if (ret != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) break;
    available_in = stream.remaining_bytes();
    next_in = stream.ConsumeBytes<uint8_t>(available_in).data();
  }
  BrotliDecoderDestroyInstance(s);

  return 0;
}