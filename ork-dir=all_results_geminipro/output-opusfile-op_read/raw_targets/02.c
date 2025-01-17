#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t slate_width = stream.ConsumeIntegral<size_t>();
  OggOpusFile* slate_image = op_open_memory(data, size, nullptr);
  if (slate_image == nullptr) {
    return 0;
  }

  const int buf_size = stream.ConsumeIntegral<int>();
  short* pcm = reinterpret_cast<short*>(malloc(buf_size * sizeof(short)));
  int li = stream.ConsumeIntegral<int>();

  op_read(slate_image, pcm, buf_size, &li);
  free(pcm);
  op_free(slate_image);
  return 0;
}