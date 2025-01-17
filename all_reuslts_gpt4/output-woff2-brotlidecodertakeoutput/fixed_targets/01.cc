#include <fuzzer/FuzzedDataProvider.h>
#include <brotli/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t available_in = stream.remaining_bytes();
  const uint8_t* next_in = stream.ConsumeRemainingBytes<uint8_t>().data();
  size_t available_out = 0;
  uint8_t* next_out = nullptr;
  BrotliDecoderState* s = BrotliDecoderCreateInstance(0, 0, 0);
  BrotliDecoderResult result = BrotliDecoderDecompressStream(s, &available_in, &next_in, &available_out, &next_out, nullptr);
  if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
    size_t out_size = 0;
    char* output = BrotliDecoderTakeOutput(s, &out_size);
    // Do something with output here, if needed.
  }
  BrotliDecoderDestroyInstance(s);
  return 0;
}