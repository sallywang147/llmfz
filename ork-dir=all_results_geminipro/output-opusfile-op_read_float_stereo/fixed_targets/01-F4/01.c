#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "opusfile/config.h"
extern "C" {
#include "opusfile/include/opusfile.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  OggOpusFile* of = op_open_memory(data, size, nullptr);
  if (of == nullptr) {
    return 0;
  }

  const int buf_size = slate_width * slate_height;
  float* pcm = new float[buf_size];
  int num_samples_read = op_read_float_stereo(of, pcm, buf_size);
  delete[] pcm;
  op_free(of);
  return num_samples_read;
}