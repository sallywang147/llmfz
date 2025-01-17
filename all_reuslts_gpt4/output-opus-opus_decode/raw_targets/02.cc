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
  OpusDecoder *decoder = opus_decoder_create(48000, 2, &error);
  if (error != OPUS_OK) {
    return 0;
  }

  int len = stream.ConsumeIntegralInRange<int>(0, size);
  std::string inputData = stream.ConsumeBytesAsString(len);
  char *dataPtr = const_cast<char*>(inputData.c_str());

  int frame_size = stream.ConsumeIntegralInRange<int>(0, 5760); // Maximum frame size is 5760
  short pcm[frame_size];

  int decode_fec = stream.ConsumeBool();

  opus_decode(decoder, dataPtr, len, pcm, frame_size, decode_fec);

  opus_decoder_destroy(decoder);
  return 0;
}