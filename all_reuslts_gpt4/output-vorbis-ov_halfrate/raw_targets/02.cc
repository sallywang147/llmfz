#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

extern "C" size_t process_vorbis_data(const uint8_t *data, size_t size) {
  OggVorbis_File vf;
  int opened = ov_open_callbacks(data, &vf, nullptr, 0, OV_CALLBACKS_NOCLOSE);
  if (opened != 0) {
    return 0;
  }
  ov_clear(&vf);
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> vorbis_data = provider.ConsumeRemainingBytes<uint8_t>();
  
  OggVorbis_File vf;
  int opened = ov_open_callbacks(vorbis_data.data(), &vf, nullptr, 0, OV_CALLBACKS_NOCLOSE);
  if (opened != 0) {
    return 0;
  }
  
  int flag = provider.ConsumeBool();
  ov_halfrate(&vf, flag);

  ov_clear(&vf);
  return 0;
}