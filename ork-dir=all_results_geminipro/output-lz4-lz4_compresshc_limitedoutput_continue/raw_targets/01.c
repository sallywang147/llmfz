#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegralInRange(0, 10000);
  std::vector<char> src(src_size);
  stream.ConsumeBytes(&src[0], src_size);
  const size_t max_dst_size = stream.ConsumeIntegralInRange(0, 10000);
  std::vector<char> dst(max_dst_size);
  LZ4_streamHC_u ctx;
  LZ4_resetStreamHC(&ctx, 1);
  const int ret = LZ4_compressHC_limitedOutput_continue(
      &ctx, &src[0], &dst[0], src_size, max_dst_size);
  if (ret < 0) {
    return 0;
  }
  return 0;
}