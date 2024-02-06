#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "7z.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t src_len = stream.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  std::vector<char> src(src_len);
  stream.ConsumeBytes(src.data(), src_len);

  size_t dest_len = stream.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  std::vector<char> dest(dest_len);

  CLzmaEncProps props;
  LzmaEncProps_Init(&props);

  size_t props_encoded_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> props_encoded(props_encoded_len);
  stream.ConsumeBytes(props_encoded.data(), props_encoded_len);

  int write_end_mark = stream.ConsumeBool();

  int ret = LzmaEncode(dest.data(), &dest_len, src.data(), src_len, &props,
                       props_encoded.data(), &props_encoded_len, write_end_mark,
                       nullptr, nullptr, nullptr);
  if (ret != SZ_OK) {
    return 0;
  }
  return 0;
}