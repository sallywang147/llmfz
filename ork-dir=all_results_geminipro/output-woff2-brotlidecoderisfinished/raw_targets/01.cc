#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "brotli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  BrotliDecoderState *s = BrotliDecoderCreateInstance(nullptr, nullptr, nullptr);
  if (s == nullptr) {
    return 0;
  }
  const size_t kBufferSize = 1024;
  std::vector<uint8_t> output_buffer(kBufferSize);
  size_t total_output = 0;
  while (BrotliDecoderIsFinished(s) == 0) {
    const size_t next_size =
        stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    auto next_input = stream.ConsumeBytes<uint8_t>(next_size);
    BrotliDecoderResult result = BrotliDecoderDecompressStream(
        s, next_input.data(), next_input.size(), &output_buffer[0],
        &output_buffer[0] + kBufferSize, &total_output, nullptr);
    if (result != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
      break;
    }
  }
  BrotliDecoderDestroyInstance(s);
  return 0;
}