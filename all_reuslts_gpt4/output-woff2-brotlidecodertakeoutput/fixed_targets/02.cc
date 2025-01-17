#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t available_out = stream.ConsumeIntegral<size_t>();
  BrotliDecoderState* s = BrotliDecoderCreateInstance(0, 0, 0);
  BrotliDecoderTakeOutput(s, &available_out);
  BrotliDecoderDestroyInstance(s);
  return 0;
}