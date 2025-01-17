#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t const max_window_log = stream.ConsumeIntegralInRange<size_t>(0, 30);
  size_t const chain_log = stream.ConsumeIntegralInRange<size_t>(0, 30);
  size_t const hash_log = stream.ConsumeIntegralInRange<size_t>(0, 30);
  size_t const search_log = stream.ConsumeIntegralInRange<size_t>(0, 30);
  size_t const min_match = stream.ConsumeIntegralInRange<size_t>(0, 255);
  size_t const target_length = stream.ConsumeIntegralInRange<size_t>(0, 255);
  size_t const strategy = stream.ConsumeIntegralInRange<size_t>(0, 3);

  ZSTD_CCtx* const cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_parameters const params = {
      .windowLog = max_window_log,
      .chainLog = chain_log,
      .hashLog = hash_log,
      .searchLog = search_log,
      .minMatch = min_match,
      .targetLength = target_length,
      .strategy = strategy,
  };
  size_t const init_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_compressionLevel, 3);
  if (ZSTD_isError(init_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const input_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* const input = new char[input_size];
  stream.ConsumeBytes(input, input_size);

  size_t const max_compressed_size = ZSTD_compressBound(input_size);
  char* const compressed = new char[max_compressed_size];
  size_t const compressed_size =
      ZSTD_compress2(cctx, compressed, max_compressed_size, input, input_size);
  if (ZSTD_isError(compressed_size)) {
    delete[] input;
    delete[] compressed;
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  delete[] input;
  delete[] compressed;
  ZSTD_freeCCtx(cctx);
  return 0;
}