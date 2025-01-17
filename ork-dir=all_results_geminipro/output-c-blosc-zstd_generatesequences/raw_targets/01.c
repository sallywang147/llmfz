#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t seq_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  char* seq = new char[seq_size];
  stream.ConsumeBytes(seq, seq_size);

  const size_t max_output_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  char* output = new char[max_output_size];

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  LZ4HC_optimal_t* opt = LZ4HC_createOptimal();

  size_t const ret =
      ZSTD_generateSequences(cctx, opt, seq_size, seq, max_output_size, output);

  ZSTD_freeCCtx(cctx);
  LZ4HC_freeOptimal(opt);
  delete[] seq;
  delete[] output;

  return ret;
}