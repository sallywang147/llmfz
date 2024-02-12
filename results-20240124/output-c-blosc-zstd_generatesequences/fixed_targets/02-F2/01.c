#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" {
#include "zstd_errors.h"
#include "zstd_seekable.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  size_t seq_size = fuzzed_data.ConsumeIntegral<size_t>();
  std::vector<char> seq_buffer(seq_size);  // modified
  fuzzed_data.ConsumeBytes<char>(seq_buffer.data(), seq_size);  // modified
  size_t max_seq_size = fuzzed_data.ConsumeIntegral<size_t>();
  size_t const ret = ZSTD_generateSequences(cctx, nullptr, max_seq_size, seq_buffer.data(), seq_size);
  if (ZSTD_isError(ret)) {
    fprintf(stderr, "Error generating sequences: %s\n", ZSTD_getErrorName(ret));
    return 0;
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}