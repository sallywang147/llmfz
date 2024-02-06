#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "opus/opus.h"

extern "C" {
#include "opus/opus.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int channels = stream.ConsumeIntegral<int>();
  const int frame_size = stream.ConsumeIntegral<int>();
  const int bitrate = stream.ConsumeIntegral<int>();
  const int max_data_bytes = stream.ConsumeIntegral<int>();
  OpusMSEncoder* st = opus_multistream_encoder_create(
      48000, channels, OPUS_APPLICATION_AUDIO, &bitrate, nullptr);
  if (st == nullptr) {
    return 0;
  }

  // Declare the opus_multistream_encode_float function.
  int opus_multistream_encode_float(OpusMSEncoder *st, const float *pcm,
                                   int frame_size, unsigned char *data,
                                   int max_data_bytes);

  std::vector<float> pcm(frame_size * channels);
  stream.ConsumeFloatingPointArray(pcm.data(), pcm.size());
  std::vector<char> data(max_data_bytes);
  const int ret = opus_multistream_encode_float(st, pcm.data(), frame_size,
                                               data.data(), max_data_bytes);
  if (ret < 0) {
    opus_multistream_encoder_destroy(st);
    return 0;
  }
  opus_multistream_encoder_destroy(st);
  return 0;
}