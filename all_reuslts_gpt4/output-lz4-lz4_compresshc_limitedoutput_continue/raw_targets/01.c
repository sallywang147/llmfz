#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <lz4.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const int srcSize = stream.ConsumeIntegralInRange<int>(1, size - 1);
  const int maxDstSize = size - srcSize;

  // Create buffers for src and dst
  std::vector<char> src(srcSize);
  std::vector<char> dst(maxDstSize);

  // Fill src buffer with data
  for (int i = 0; i < srcSize; ++i) {
    src[i] = stream.ConsumeIntegral<char>();
  }

  // Create and initialize LZ4_streamHC_t structure
  LZ4_streamHC_t* ctx = LZ4_createStreamHC();
  if (ctx == nullptr) {
    return 0;
  }

  LZ4_compressHC_limitedOutput_continue(ctx, src.data(), dst.data(), srcSize, maxDstSize);

  LZ4_freeStreamHC(ctx);
  
  return 0;
}