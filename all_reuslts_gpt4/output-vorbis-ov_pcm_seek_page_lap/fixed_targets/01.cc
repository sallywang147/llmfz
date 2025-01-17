#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

static size_t read_func(void* ptr, size_t size, size_t nmemb, void* datasource) {
  FuzzedDataProvider* provider =
      reinterpret_cast<FuzzedDataProvider*>(datasource);
  const size_t bytes_to_read = size * nmemb;
  if (bytes_to_read == 0) {
    return 0;
  }
  const std::vector<uint8_t> data = provider->ConsumeBytes<uint8_t>(bytes_to_read);
  if (data.empty()) {
    return 0;
  }
  memcpy(ptr, data.data(), data.size());
  return data.size() / size;
}

static int seek_func(void* datasource, ogg_int64_t offset, int whence) {
  return 0;
}

static int close_func(void* datasource) {
  return 0;
}

static long tell_func(void* datasource) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static const ov_callbacks callbacks = {
      read_func, seek_func, close_func, tell_func};
  FuzzedDataProvider provider(data, size);
  OggVorbis_File vf;
  if (ov_open_callbacks(&provider, &vf, nullptr, 0, callbacks) != 0) {
    return 0;
  }

  size_t pos = provider.ConsumeIntegral<size_t>();
  ov_pcm_seek_page_lap(&vf, pos);

  ov_clear(&vf);
  return 0;
}