 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  size_t seq_size = fuzzed_data.ConsumeIntegral<size_t>();
  char* seq_buffer = fuzzed_data.ConsumeBytes<char>(seq_size);
  size_t max_seq_size = fuzzed_data.ConsumeIntegral<size_t>();
  ZSTD_generateSequences(cctx, nullptr, max_seq_size, seq_buffer, seq_size);
  ZSTD_freeCCtx(cctx);
  return 0;
}