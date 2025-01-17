#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ov_init();
    initialized = true;
  }

  OggVorbis_File vf;
  FuzzedDataProvider provider(data, size);

  if(ov_open_callbacks(data, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
    return 0;
  }

  size_t pos = provider.ConsumeIntegral<size_t>();
  ov_pcm_seek(&vf, pos);

  ov_clear(&vf);

  return 0;
}