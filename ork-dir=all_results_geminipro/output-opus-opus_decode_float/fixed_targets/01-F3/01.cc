#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "opus/opus.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int sample_rate = stream.ConsumeIntegralInRange(8000, 48000);
  const int channels = stream.ConsumeIntegralInRange(1, 2);
  const int frame_size = stream.ConsumeIntegralInRange(20, 120);
  const int decode_fec = stream.ConsumeBool();

  OpusDecoder* decoder = opus_decoder_create(sample_rate, channels, stream.ConsumeIntegral<int>());
  if (decoder == nullptr) {
    return 0;
  }

  const size_t pcm_size = frame_size * channels * sizeof(float);
  float* pcm = static_cast<float*>(std::malloc(pcm_size));
  if (pcm == nullptr) {
    opus_decoder_destroy(decoder);
    return 0;
  }

  const std::string input = stream.ConsumeRemainingBytesAsString();
  int decoded_samples = opus_decode_float(decoder, input.data(), input.size(), pcm, frame_size, decode_fec);
  if (decoded_samples < 0) {
    opus_decoder_destroy(decoder);
    std::free(pcm);
    return 0;
  }

  std::free(pcm);
  opus_decoder_destroy(decoder);
  return 0;
}
```

The issue was that `opus_decode_float` returns the number of decoded samples, which can be negative in case of an error. The original code didn't check the return value and always freed the `pcm` buffer, even if the decoding failed. This could lead to undefined behavior if the buffer was already freed.

The fixed code checks the return value of `opus_decode_float` and only frees the `pcm` buffer if the decoding was successful.