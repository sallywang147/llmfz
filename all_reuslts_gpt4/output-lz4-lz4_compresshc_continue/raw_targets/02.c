#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "lz4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  const int srcSize = stream.ConsumeIntegralInRange<int>(1, size);
  std::string src = stream.ConsumeBytesAsString(srcSize);
  const int maxDstSize = LZ4_compressBound(srcSize);
  std::vector<char> dst(maxDstSize);

  LZ4_streamHC_t* ctx = LZ4_createStreamHC();
  if (ctx == nullptr) {
    return 0;
  }

  LZ4_compressHC_continue(ctx, src.data(), dst.data(), srcSize);

  LZ4_freeStreamHC(ctx);

  return 0;
}