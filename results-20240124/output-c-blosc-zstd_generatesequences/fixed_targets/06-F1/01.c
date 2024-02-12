#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t seq_size = provider.ConsumeIntegral<size_t>();
  size_t max_size = provider.ConsumeIntegral<size_t>();
  size_t max_output_size = provider.ConsumeIntegral<size_t>();
  char* output = new char[max_output_size];
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  size_t ret = ZSTD_generateSequences(cctx, nullptr, seq_size, output, max_output_size);
  ZSTD_freeCCtx(cctx);
  delete[] output;
  return 0;
}