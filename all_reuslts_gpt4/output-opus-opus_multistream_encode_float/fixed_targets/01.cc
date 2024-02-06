#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <opus/opus_multistream.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the OpusMSEncoder
  int error;
  int Fs = 48000; // sample rate
  int channels = 2; // number of channels
  int coupled_streams = 1; // number of coupled streams
  unsigned char mapping[2] = {0, 1}; // channel mapping
  OpusMSEncoder *st = opus_multistream_encoder_create(Fs, channels, coupled_streams, channels - coupled_streams, mapping, OPUS_APPLICATION_AUDIO, &error);

  if (error != OPUS_OK || st == NULL) {
    return 0;
  }

  // Prepare the input and output buffers
  int frame_size = stream.ConsumeIntegralInRange(0, 5760); // frame size must be between 0 and 5760
  float *pcm = new float[frame_size * channels];
  for (int i = 0; i < frame_size * channels; i++) {
    pcm[i] = stream.ConsumeFloatingPointInRange(-1.0, 1.0);
  }
  int max_data_bytes = stream.ConsumeIntegralInRange(0, 4000); // max_data_bytes must be between 0 and 4000
  char *data_out = new char[max_data_bytes];

  // Call the function to fuzz
  opus_multistream_encode_float(st, pcm, frame_size, data_out, max_data_bytes);

  // Clean up
  delete[] pcm;
  delete[] data_out;
  opus_multistream_encoder_destroy(st);

  return 0;
}