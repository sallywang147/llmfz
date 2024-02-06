#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "opus/opus.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int channels = stream.ConsumeIntegral<int>() % 3 + 1;
  const int frame_size = stream.ConsumeIntegral<int>() % 1920 + 1;
  float* pcm = new float[channels * frame_size];
  for (int i = 0; i < channels * frame_size; ++i) {
    pcm[i] = stream.ConsumeFloatingPoint<float>();
  }
  OpusProjectionEncoder* st = opus_projection_encoder_create(
      48000, channels, OPUS_APPLICATION_VOIP, &stream);
  if (st == nullptr) {
    delete[] pcm;
    return 0;
  }
  const int max_data_bytes = stream.ConsumeIntegralInRange(0, 1024);
  char* data = new char[max_data_bytes];
  int ret = opus_projection_encode_float(st, pcm, frame_size, data,
                                         max_data_bytes);
  delete[] pcm;
  delete[] data;
  opus_projection_encoder_destroy(st);
  return 0;
}