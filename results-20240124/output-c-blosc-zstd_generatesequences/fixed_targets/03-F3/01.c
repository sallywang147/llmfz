#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "zstd.h"
extern "C" {
#include "lz4hc.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  LZ4HC_CCtx* lz4hc_ctx = LZ4HC_create();
  if (lz4hc_ctx == nullptr) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  const size_t seq_size = stream.ConsumeIntegralInRange<size_t>(0, 1000000);
  std::vector<char> seq(seq_size);
  stream.ConsumeBytes(seq.data(), seq_size);

  size_t generated_size = ZSTD_generateSequences(cctx, lz4hc_ctx, seq_size,
                                                   seq.data(), seq_size);

  LZ4HC_free(lz4hc_ctx);
  ZSTD_freeCCtx(cctx);

  return generated_size;
}