 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer inbuf;
  inbuf.src = stream.ConsumeRemainingBytes();
  inbuf.size = stream.remaining_bytes();
  inbuf.pos = 0;

  ZSTD_endStream(cctx, &inbuf);
  ZSTD_freeCCtx(cctx);

  return 0;
}