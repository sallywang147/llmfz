#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "opus/opus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int channels = stream.ConsumeIntegral<int>();
  const int sample_rate = stream.ConsumeIntegral<int>();
  const int analysis_frame_size = stream.ConsumeIntegral<int>();
  const int max_data_bytes = stream.ConsumeIntegral<int>();
  OpusEncoder* encoder = opus_encoder_create(sample_rate, channels, OPUS_APPLICATION_AUDIO, &stream.ConsumeIntegral<int>());
  if (encoder == nullptr) {
    return 0;
  }

  std::vector<float> pcm(analysis_frame_size * channels);
  stream.ConsumeFloatingPointArray<float>(pcm.data(), pcm.size());
  std::vector<char> encoded_data(max_data_bytes);
  const int encoded_data_size = opus_encode_float(
      encoder, pcm.data(), analysis_frame_size, encoded_data.data(),
      encoded_data.size());
  if (encoded_data_size < 0) {
    opus_encoder_destroy(encoder);
    return 0;
  }

  opus_encoder_destroy(encoder);
  return 0;
}