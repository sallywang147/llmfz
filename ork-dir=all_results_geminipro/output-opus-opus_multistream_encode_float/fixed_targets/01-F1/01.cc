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
  const int rate = stream.ConsumeIntegralInRange<int>(8000, 48000);
  const int application = stream.ConsumeIntegralInRange<int>(OPUS_APPLICATION_VOIP,
                                                           OPUS_APPLICATION_AUDIO);
  OpusMSEncoder* st = opus_multistream_encoder_create(rate, channels, application,
                                                    nullptr);
  if (st == nullptr) {
    return 0;
  }

  const int frame_size = stream.ConsumeIntegralInRange<int>(20, 960);
  const size_t data_size = stream.ConsumeIntegralInRange<size_t>(1024, 4096);
  char* data = new char[data_size];
  float* pcm = new float[frame_size * channels];

  stream.ConsumeFloatArray(pcm, frame_size * channels);
  const int ret = opus_multistream_encode_float(st, pcm, frame_size, data,
                                                data_size);
  if (ret < 0) {
    fprintf(stderr, "opus_multistream_encode_float failed with error %d\n", ret);
  }

  opus_multistream_encoder_destroy(st);
  delete[] data;
  delete[] pcm;
  return 0;
}