#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" {
#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer in_buffer;
  in_buffer.src = data;
  in_buffer.size = size;
  in_buffer.pos = 0;

  ZSTD_outBuffer out_buffer;
  out_buffer.dst = nullptr;
  out_buffer.size = 0;
  out_buffer.pos = 0;

  size_t ret;
  while ((ret = ZSTD_compressStream(cctx, &out_buffer, &in_buffer)) > 0) {
    out_buffer.pos = 0;
  }
  if (ret == 0) {
    ZSTD_endStream(cctx, &in_buffer);
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}