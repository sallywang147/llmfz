 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZSTD_CCtx* context = ZSTD_createCCtx();
  if (context == nullptr) {
    return 0;
  }

  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::vector<uint8_t> src_data = stream.ConsumeBytes<uint8_t>(src_size);
  const size_t dst_size = ZSTD_compressBound(src_size);
  std::vector<uint8_t> dst_data(dst_size);

  const size_t ret = ZSTD_compress2(context, dst_data.data(), dst_size,
                                    src_data.data(), src_size);
  ZSTD_freeCCtx(context);
  return 0;
}