#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "opus/opus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int channels = stream.ConsumeIntegralInRange<int>(1, 2);
  const int sample_rate = stream.ConsumeIntegralInRange<int>(8000, 48000);
  const int frame_size = stream.ConsumeIntegralInRange<int>(120, 960);
  const int decode_fec = stream.ConsumeBool();

  OpusDecoder* decoder = opus_decoder_create(sample_rate, channels, &stream.ConsumeIntegral<int>());
  if (decoder == nullptr) {
    return 0;
  }

  const size_t data_size = stream.ConsumeRemainingBytes<uint8_t>().size();
  char* data_ptr = reinterpret_cast<char*>(stream.ConsumeRemainingBytes<uint8_t>().data());

  std::vector<int16_t> pcm(frame_size * channels);
  int status = opus_decode(decoder, data_ptr, data_size, pcm.data(), frame_size, decode_fec);
  opus_decoder_destroy(decoder);

  return 0;
}