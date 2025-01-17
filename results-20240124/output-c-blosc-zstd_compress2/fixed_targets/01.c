 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t src_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t dst_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t level = stream.ConsumeIntegral<uint8_t>();
  const std::string input = stream.ConsumeRemainingBytesAsString();

  char* src = (char*)malloc(src_size);
  memcpy(src, input.c_str(), src_size);
  char* dst = (char*)malloc(dst_size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  size_t compressed_size = ZSTD_compress2(cctx, dst, dst_size, src, src_size);

  free(src);
  free(dst);
  ZSTD_freeCCtx(cctx);
  return 0;
}