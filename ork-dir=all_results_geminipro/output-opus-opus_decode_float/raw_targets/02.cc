#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "opus/opus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int frame_size = stream.ConsumeIntegral<int>();
  const int decode_fec = stream.ConsumeIntegral<int>();
  const std::string input_data = stream.ConsumeRemainingBytesAsString();

  OpusDecoder* decoder = opus_decoder_create(48000, 2, &frame_size);
  if (decoder == nullptr) {
    return 0;
  }

  float* pcm = static_cast<float*>(calloc(frame_size * 2, sizeof(float)));
  if (pcm == nullptr) {
    opus_decoder_destroy(decoder);
    return 0;
  }

  int result = opus_decode_float(decoder, input_data.data(), input_data.size(), pcm, frame_size, decode_fec);
  if (result < 0) {
    opus_decoder_destroy(decoder);
    free(pcm);
    return 0;
  }

  opus_decoder_destroy(decoder);
  free(pcm);
  return 0;
}