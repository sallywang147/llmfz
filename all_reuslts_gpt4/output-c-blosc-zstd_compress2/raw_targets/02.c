#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Split the input into two parts to use as source and destination buffers.
  const size_t src_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::string src = provider.ConsumeBytesAsString(src_size);
  std::string dst = provider.ConsumeRemainingBytesAsString();

  // Ensure the destination buffer is large enough to hold the compressed data.
  size_t dst_capacity = ZSTD_compressBound(src.size());
  if (dst_capacity > dst.size()) {
    dst.resize(dst_capacity);
  }

  // Call the function to fuzz
  ZSTD_compress2(cctx, dst.data(), dst.size(), src.data(), src.size());

  ZSTD_freeCCtx(cctx);

  return 0;
}