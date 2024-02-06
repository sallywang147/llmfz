#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "opus/opus.h"

extern "C" {
#include "opus/opus_header.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an Opus decoder.
  OpusDecoder* decoder = opus_decoder_create(48000, 2, &stream);
  if (decoder == nullptr) {
    return 0;
  }

  // Decode the input data.
  const int frame_size = 960;  // 20 ms at 48 kHz.
  short pcm[frame_size * 2];
  while (stream.remaining_bytes() >= frame_size) {
    const int len = stream.ConsumeIntegralInRange<int>(0, 1024);
    char* data_ptr = stream.ConsumeBytes<char>(len);
    int decode_fec = stream.ConsumeBool();
    int ret = opus_decode(decoder, data_ptr, len, pcm, frame_size, decode_fec);
    if (ret < 0) {
      break;
    }
  }

  // Destroy the Opus decoder.
  opus_decoder_destroy(decoder);

  return 0;
}