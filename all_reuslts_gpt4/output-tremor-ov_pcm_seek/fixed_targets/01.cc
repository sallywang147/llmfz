#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

size_t read_func(void *ptr, size_t size, size_t nmemb, void *datasource) {
  FuzzedDataProvider* data_provider = static_cast<FuzzedDataProvider*>(datasource);
  const size_t max_length = size * nmemb;
  const std::vector<uint8_t> data = data_provider->ConsumeBytes<uint8_t>(max_length);
  std::memcpy(ptr, data.data(), data.size());
  return data.size();
}

int seek_func(void *datasource, ogg_int64_t offset, int whence) {
  return 0;
}

int close_func(void *datasource) {
  return 0;
}

long tell_func(void *datasource) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  ov_callbacks callbacks = {
      .read_func = read_func,
      .seek_func = seek_func,
      .close_func = close_func,
      .tell_func = tell_func,
  };

  OggVorbis_File vf;
  if (ov_open_callbacks(&data_provider, &vf, NULL, 0, callbacks) != 0) {
    return 0;
  }

  size_t pos = data_provider.ConsumeIntegral<size_t>();
  ov_pcm_seek(&vf, pos);

  ov_clear(&vf);
  return 0;
}