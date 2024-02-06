#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "LzmaLib.h"
#include "LzmaDec.h"

extern "C" {
#include "7zTypes.h"
#include "7zAlloc.h"
#include "7zCrc.h"
#include "LzmaEnc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t src_len = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  std::vector<uint8_t> src(src_len);
  stream.ConsumeBytes<uint8_t>(&src[0], src_len);

  size_t dest_len = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  std::vector<uint8_t> dest(dest_len);
  size_t dest_len_out;

  CLzmaEncProps props;
  LzmaEncProps_Init(&props);

  size_t props_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  std::vector<uint8_t> props_encoded(props_size);
  size_t props_size_out;

  int write_end_mark = stream.ConsumeBool();

  SRes res = LzmaEncode(&dest[0], &dest_len_out, &src[0], src_len, &props,
                        &props_encoded[0], &props_size_out, write_end_mark, NULL,
                        NULL, NULL);
  if (res != SZ_OK) {
    return 0;
  }

  return 0;
}