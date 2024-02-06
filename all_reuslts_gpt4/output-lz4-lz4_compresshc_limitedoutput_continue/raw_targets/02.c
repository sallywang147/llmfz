#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <lz4.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  const int srcSize = stream.ConsumeIntegralInRange<int>(1, size);
  std::string src = stream.ConsumeBytesAsString(srcSize);

  LZ4_streamHC_t* ctx = LZ4_createStreamHC();
  if (!ctx) {
    return 0;
  }

  std::vector<char> dst(LZ4_compressBound(srcSize));
  int maxDstSize = dst.size();

  LZ4_compressHC_limitedOutput_continue(ctx, src.data(), dst.data(), srcSize, maxDstSize);

  LZ4_freeStreamHC(ctx);
  return 0;
}