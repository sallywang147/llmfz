#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ov_init();
    initialized = true;
  }

  OggVorbis_File vf;
  int ret = ov_open_callbacks(data, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE);
  if (ret < 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  double pos = provider.ConsumeFloatingPoint<double>();

  ov_time_seek_page_lap(&vf, pos);

  ov_clear(&vf);

  return 0;
}