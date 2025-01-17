#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opus/opus.h>
#include <opus/opus_projection.h>
#include <fuzzer/FuzzedDataProvider.h>

// Opus Projection Encoding fuzzing wrapper to help with automated fuzz testing.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int channels = stream.ConsumeIntegralInRange<int>(1, 255);
  int frame_size = stream.ConsumeIntegralInRange<int>(1, 5760);
  int max_data_bytes = stream.ConsumeIntegralInRange<int>(1, 4000);

  // Create a projection encoder
  int err;
  OpusProjectionEncoder* encoder = opus_projection_ambisonics_encoder_create(48000, channels, 1, &err);
  if (err != OPUS_OK) {
    return 0;
  }

  // Allocate memory for pcm and data
  float* pcm = (float*) malloc(sizeof(float) * frame_size * channels);
  char* data = (char*) malloc(max_data_bytes);

  // Fill the pcm array with random floats
  for (int i = 0; i < frame_size * channels; i++) {
    pcm[i] = stream.ConsumeFloatingPoint<float>();
  }

  // Call the function to fuzz
  opus_projection_encode_float(encoder, pcm, frame_size, data, max_data_bytes);

  // Clean up
  free(pcm);
  free(data);
  opus_projection_encoder_destroy(encoder);

  return 0;
}