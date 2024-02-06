#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    if (ov_init() != 0) {
      return 0;
    }
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  OggVorbis_File vf;
  int ret = ov_open_callbacks(&provider, &vf, nullptr, 0, OV_CALLBACKS_NOCLOSE);
  if (ret < 0) {
    return 0;
  }

  size_t pos = provider.ConsumeIntegral<size_t>();
  ov_pcm_seek_lap(&vf, pos);

  ov_clear(&vf);
  return 0;
}