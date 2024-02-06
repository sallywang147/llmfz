#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/vorbisfile.h"

extern "C" size_t ov_read(void *ptr, size_t size, size_t nmemb, void *datasource) {
  FuzzedDataProvider* provider = static_cast<FuzzedDataProvider*>(datasource);
  const size_t max_bytes = size * nmemb;
  const size_t actual_bytes = provider->ConsumeIntegralInRange<size_t>(0, max_bytes);
  auto data = provider->ConsumeBytes<uint8_t>(actual_bytes);
  memcpy(ptr, data.data(), data.size());
  return data.size() / size;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static ov_callbacks callbacks = {
      .read_func = ov_read,
      .seek_func = nullptr,
      .close_func = nullptr,
      .tell_func = nullptr,
  };
  
  FuzzedDataProvider provider(data, size);
  OggVorbis_File vf;
  int ret = ov_test_callbacks(&provider, &vf, nullptr, 0, callbacks);
  if (ret != 0) {
    return 0;
  }

  ret = ov_test_open(&vf);
  if (ret != 0) {
    ov_clear(&vf);
    return 0;
  }

  ov_clear(&vf);

  return 0;
}