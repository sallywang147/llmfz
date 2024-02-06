#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <lzo/lzoconf.h>
#include <lzo/lzo1x.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t in_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  auto in = stream.ConsumeBytes<char>(in_len);
  const size_t out_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char out[out_len];
  const size_t wrkmem_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char wrkmem[wrkmem_len];
  const size_t dict_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char dict[dict_len];
  lzo1x_999_compress_dict(in.data(), in_len, out, &out_len, wrkmem, dict, dict_len, LZO_IGNORE);
  return 0;
}