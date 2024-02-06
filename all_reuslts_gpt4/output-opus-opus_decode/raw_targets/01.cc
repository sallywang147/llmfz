#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <opus/opus.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int error;
  int sample_rate = 48000;  // Opus supports 8, 12, 16, 24, and 48 kHz.
  int channel_count = 2;    // Opus supports up to 255 channels, but we'll limit to stereo for simplicity.
  OpusDecoder *decoder = opus_decoder_create(sample_rate, channel_count, &error);
  if (error != OPUS_OK) {
    return 0;
  }

  int len = stream.ConsumeIntegralInRange<int>(1, size);
  std::string inputData = stream.ConsumeBytesAsString(len);
  char *dataPtr = const_cast<char *>(inputData.c_str());

  int frame_size = 5760;  // Maximum frame size is 5760 samples.
  short *pcm = (short *)malloc(frame_size * sizeof(short));
  if (!pcm) {
    opus_decoder_destroy(decoder);
    return 0;
  }

  int decode_fec = stream.ConsumeBool();

  opus_decode(decoder, dataPtr, len, pcm, frame_size, decode_fec);

  free(pcm);
  opus_decoder_destroy(decoder);

  return 0;
}