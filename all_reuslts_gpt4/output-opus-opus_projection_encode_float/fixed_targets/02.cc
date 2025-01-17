#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <opus/opus.h>
#include <opus/opus_projection.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int channels = 2;
  int application = OPUS_APPLICATION_AUDIO;
  int sample_rate = 48000;
  int frame_size = 960;
  int max_data_bytes = 4000;

  int error;
  OpusProjectionEncoder* encoder = opus_projection_ambisonics_encoder_create(
      sample_rate, channels, 1, &error);
  if (error != OPUS_OK || encoder == NULL) {
    return 0;
  }

  std::vector<float> pcm = stream.ConsumeBytes<float>(frame_size * channels);
  std::string output_data(max_data_bytes, 0);

  opus_projection_encode_float(encoder, pcm.data(), frame_size,
                               &output_data[0], max_data_bytes);

  opus_projection_encoder_destroy(encoder);
  return 0;
}