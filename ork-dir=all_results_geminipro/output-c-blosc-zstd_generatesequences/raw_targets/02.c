#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(1, 1024 * 1024);
  char* buffer = new char[buffer_size];
  const size_t sequences_size = stream.ConsumeIntegralInRange<size_t>(1, 1024 * 1024);
  char* sequences = new char[sequences_size];
  const size_t max_sequences = stream.ConsumeIntegralInRange<size_t>(1, 1024 * 1024);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  LZ4HC_optimal_t* opt = LZ4HC_createOptimal();

  size_t result = ZSTD_generateSequences(cctx, opt, max_sequences, sequences, sequences_size);
  if (ZSTD_isError(result)) {
    printf("ZSTD_generateSequences returned an error: %s\n", ZSTD_getErrorName(result));
    goto cleanup;
  }

  result = ZSTD_compressCCtx(cctx, buffer, buffer_size, sequences, result);
  if (ZSTD_isError(result)) {
    printf("ZSTD_compressCCtx returned an error: %s\n", ZSTD_getErrorName(result));
    goto cleanup;
  }

cleanup:
  delete[] buffer;
  delete[] sequences;
  ZSTD_freeCCtx(cctx);
  LZ4HC_freeOptimal(opt);
  return 0;
}