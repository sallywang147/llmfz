 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int compression_level = provider.ConsumeIntegralInRange<int>(-1, 22);
  ZSTD_CCtx* context = ZSTD_createCCtx();
  ZSTD_CCtx_setParameter(context, ZSTD_c_compressionLevel, compression_level);
  ZSTD_inBuffer input;
  input.src = provider.ConsumeBytes<uint8_t>(provider.remaining_bytes()).data();
  input.size = provider.remaining_bytes();
  input.pos = 0;
  ZSTD_outBuffer output;
  output.dst = nullptr;
  output.size = 0;
  output.pos = 0;
  size_t ret = ZSTD_compressStream(context, &output, &input);
  ZSTD_freeCCtx(context);
  return 0;
}