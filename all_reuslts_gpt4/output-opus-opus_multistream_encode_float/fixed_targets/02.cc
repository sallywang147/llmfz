#include <stdint.h>
#include <stdlib.h>
#include <opus/opus.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int channels = 2;
  int application = OPUS_APPLICATION_AUDIO;
  int err;
  int frame_size = 960; // 20ms @ 48kHz
  int max_data_bytes = 4000; // Maximum output payload size

  OpusMSEncoder *encoder = opus_multistream_encoder_create(48000, channels, 1, 1, &err);
  if (err != OPUS_OK) {
    return 0;
  }

  std::vector<float> pcm = stream.ConsumeBytes<float>(frame_size * channels);
  std::vector<char> output_data(max_data_bytes);

  if (pcm.size() < frame_size * channels) {
    opus_multistream_encoder_destroy(encoder);
    return 0;
  }

  opus_multistream_encode_float(encoder, pcm.data(), frame_size, output_data.data(), max_data_bytes);

  opus_multistream_encoder_destroy(encoder);
  return 0;
}