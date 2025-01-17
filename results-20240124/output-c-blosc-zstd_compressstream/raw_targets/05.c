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
  size_t compressed_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto compressed_data = provider.ConsumeBytes<unsigned char>(compressed_size);
  ZSTD_inBuffer input = {compressed_data.data(), compressed_data.size(), 0};
  ZSTD_inBuffer output = {nullptr, 0, 0};
  size_t ret = ZSTD_compressStream(cctx, &output, &input);
  if (ZSTD_isError(ret)) {
    fprintf(stderr, "ZSTD_compressStream error: %s\n", ZSTD_getErrorName(ret));
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}