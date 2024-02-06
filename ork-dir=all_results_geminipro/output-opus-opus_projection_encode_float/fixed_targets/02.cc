#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "opus/opus.h"

extern "C" {
#include "opus/opus_projection.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int32_t channels = stream.ConsumeIntegral<int32_t>();
  const int32_t frame_size = stream.ConsumeIntegral<int32_t>();
  const int32_t max_data_bytes = stream.ConsumeIntegral<int32_t>();
  float* pcm = reinterpret_cast<float*>(stream.ConsumeBytes<float>(frame_size * channels * sizeof(float)));
  char* data_out = reinterpret_cast<char*>(stream.ConsumeBytes<char>(max_data_bytes));
  OpusProjectionEncoder* st = opus_projection_encoder_create(channels, 48000, OPUS_APPLICATION_VOIP, &stream.ConsumeIntegral<int32_t>());
  if (st == nullptr) {
    return 0;
  }
  const int ret = opus_projection_encode_float(st, pcm, frame_size, data_out, max_data_bytes);
  opus_projection_encoder_destroy(st);
  return ret;
}