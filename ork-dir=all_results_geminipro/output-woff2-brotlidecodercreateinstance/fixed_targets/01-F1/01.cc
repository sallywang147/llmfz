#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "brotli/decode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Allocate a BrotliDecoderStateStruct.
  BrotliDecoderState* state = BrotliDecoderCreateInstance(
      nullptr, nullptr, nullptr);
  if (state == nullptr) {
    return 0;
  }

  // Decode the data.
  size_t decoded_size = 0;
  const uint8_t* decoded_data = BrotliDecoderDecompressStream(
      state, provider.remaining_bytes(), provider.ConsumeRemainingBytes(),
      &decoded_size, nullptr);
  if (decoded_data == nullptr) {
    BrotliDecoderDestroyInstance(state);
    return 0;
  }

  // Free the allocated memory.
  BrotliDecoderDestroyInstance(state);
  return 0;
}