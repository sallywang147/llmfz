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

  std::vector<float> pcm(480 * 2);
  int frame_size = 480;
  int decode_fec = stream.ConsumeBool();

  std::vector<uint8_t> opus_data = stream.ConsumeRemainingBytes<uint8_t>();
  char *data_ptr = reinterpret_cast<char*>(opus_data.data());
  int len = opus_data.size();

  opus_decode_float(decoder, data_ptr, len, pcm.data(), frame_size, decode_fec);

  opus_decoder_destroy(decoder);
  return 0;
}