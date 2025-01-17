#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "brotli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BrotliDecoderState* state = BrotliDecoderCreateInstance(
      nullptr, nullptr, nullptr);
  if (state == nullptr) {
    return 0;
  }

  size_t total_output = 0;
  while (stream.remaining_bytes() > 0) {
    size_t consumed = 0;
    size_t produced = 0;
    if (!BrotliDecoderDecompressStream(
            state, stream.ConsumeRemainingBytes().data(),
            stream.remaining_bytes(), &consumed, &produced, nullptr)) {
      break;
    }
    total_output += produced;
  }

  BrotliDecoderDestroyInstance(state);

  return 0;
}