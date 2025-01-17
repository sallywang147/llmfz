#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <opus/opus.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a new encoder state in stack.
  int error;
  OpusEncoder *encoder = opus_encoder_create(48000, 2, OPUS_APPLICATION_AUDIO, &error);
  if (error != OPUS_OK) {
    return 0;
  }

  // Consume data for pcm and out_data.
  size_t out_data_bytes = stream.ConsumeIntegralInRange<size_t>(1, size);
  size_t analysis_frame_size = out_data_bytes / sizeof(float);
  std::vector<float> pcm = stream.ConsumeBytes<float>(analysis_frame_size);
  std::vector<char> out_data(out_data_bytes);

  // Call the function to be fuzzed.
  opus_encode_float(encoder, pcm.data(), analysis_frame_size, out_data.data(), out_data_bytes);

  // Clean up.
  opus_encoder_destroy(encoder);

  return 0;
}