#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  ZSTD_inBuffer in_buffer;
  ZSTD_outBuffer out_buffer;
  in_buffer.src = stream.ConsumeRemainingBytes<const uint8_t*>().data();
  in_buffer.size = in_buffer.src.size();
  in_buffer.pos = 0;
  out_buffer.dst = std::vector<uint8_t>(stream.ConsumeIntegralInRange<size_t>(
      0,
      1 << 20));
  out_buffer.size = out_buffer.dst.size();
  out_buffer.pos = 0;
  size_t ret = ZSTD_compressStream(cctx, &out_buffer, &in_buffer);
  ZSTD_freeCCtx(cctx);
  return 0;
}
}