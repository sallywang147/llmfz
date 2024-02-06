#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  OggOpusFile* slate_image = op_open_memory(data, size, nullptr);
  if (slate_image == nullptr) {
    return 0;
  }

  const int x_position = stream.ConsumeIntegral<int>();
  const int y_position = stream.ConsumeIntegral<int>();
  const int text_color = stream.ConsumeIntegral<int>();
  const int buf_size = stream.ConsumeIntegral<int>();
  int li = 0;
  float pcm[buf_size];
  op_read_float(slate_image, pcm, buf_size, &li);
  op_free(slate_image);
  return 0;
}