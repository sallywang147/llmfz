#include <stdint.h>
#include <stdlib.h>

#include <opus/opus.h>
#include <fuzzer/FuzzedDataProvider.h>

#define MAX_FRAME_SIZE 6*960

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
  std::string str_data = stream.ConsumeBytesAsString(len);
  char *data_ptr = const_cast<char*>(str_data.c_str());

  std::vector<float> pcm(MAX_FRAME_SIZE * 2);
  int frame_size = stream.ConsumeIntegralInRange<int>(0, MAX_FRAME_SIZE);
  int decode_fec = stream.ConsumeBool();

  opus_decode_float(decoder, data_ptr, len, pcm.data(), frame_size, decode_fec);

  opus_decoder_destroy(decoder);

  return 0;
}