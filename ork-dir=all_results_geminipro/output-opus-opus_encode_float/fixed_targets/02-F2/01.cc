#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "opus/opus.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int channels = stream.ConsumeIntegralInRange<int>(1, 2);
  const int sample_rate = stream.ConsumeIntegralInRange<int>(8000, 48000);
  const int bitrate = stream.ConsumeIntegralInRange<int>(8000, 128000);
  const int complexity = stream.ConsumeIntegralInRange<int>(0, 10);
  const int application = stream.ConsumeIntegralInRange<int>(0, 20);

  OpusEncoder* encoder = opus_encoder_create(sample_rate, channels, application, &bitrate);
  if (encoder == nullptr) {
    return 0;
  }
  opus_encoder_ctl(encoder, OPUS_SET_COMPLEXITY(complexity));

  const int frame_size = 960;
  std::vector<float> pcm(frame_size * channels);
  for (auto& sample : pcm) {
    sample = stream.ConsumeFloat<float>();
  }

  std::vector<char> encoded(frame_size * channels * 3);
  int encoded_size = opus_encode_float(encoder, pcm.data(), frame_size,
                                       encoded.data(), encoded.size());
  if (encoded_size < 0) {
    opus_encoder_destroy(encoder);
    return 0;
  }

  opus_encoder_destroy(encoder);
  return 0;
}