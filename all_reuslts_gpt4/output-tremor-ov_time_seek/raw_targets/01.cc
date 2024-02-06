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
    ov_init();
    initialized = true;
  }

  OggVorbis_File vf;
  int ret;
  
  FuzzedDataProvider provider(data, size);
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
  
  if(ov_open_callbacks(next_input.data(), &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
    return 0;
  }

  size_t milliseconds = provider.ConsumeIntegral<size_t>();
  ret = ov_time_seek(&vf, milliseconds);
  
  ov_clear(&vf);

  return 0;
}