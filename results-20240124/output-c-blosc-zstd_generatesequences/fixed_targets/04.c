#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "zstd.h"
#include "zstd_internal.h"

extern "C" {
#include "zstd_compress_sequences.h"
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  LZ4HC_optimal_t opt;
  size_t max_seq_size = fdp.ConsumeIntegral<size_t>();
  char *seq = fdp.ConsumeBytes<char>(max_seq_size);
  size_t seq_size = fdp.ConsumeIntegral<size_t>();
  ZSTD_generateSequences(cctx, &opt, max_seq_size, seq, seq_size);
  ZSTD_freeCCtx(cctx);
  return 0;
}