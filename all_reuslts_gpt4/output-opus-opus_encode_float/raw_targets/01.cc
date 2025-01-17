#include <stdint.h>
#include <stdlib.h>
#include <opus/opus.h>
#include <fuzzer/FuzzedDataProvider.h>

#define MAX_FRAME_SIZE 6*960
#define MAX_PACKET_SIZE (3*1276)

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int error;
  OpusEncoder *enc = opus_encoder_create(48000, 2, OPUS_APPLICATION_AUDIO, &error);
  if (error != OPUS_OK) {
    opus_encoder_destroy(enc);
    return 0;
  }

  float pcm[MAX_FRAME_SIZE];
  char cbits[MAX_PACKET_SIZE];
  int frame_size = stream.ConsumeIntegralInRange(0, MAX_FRAME_SIZE);
  int nbBytes = stream.ConsumeIntegralInRange(0, MAX_PACKET_SIZE);

  for (int i = 0; i < frame_size; i++) {
    pcm[i] = stream.ConsumeFloatingPoint<float>();
  }

  opus_encode_float(enc, pcm, frame_size, cbits, nbBytes);

  opus_encoder_destroy(enc);
  return 0;
}