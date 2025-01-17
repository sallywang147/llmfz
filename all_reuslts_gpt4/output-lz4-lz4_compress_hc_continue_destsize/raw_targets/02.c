#include <fuzzer/FuzzedDataProvider.h>
#include <lz4.h>
#include <lz4hc.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Get the size of the source buffer
  const int srcSize = stream.ConsumeIntegralInRange<int>(0, size);

  // Create a source buffer and populate it with data
  std::vector<char> src(srcSize);
  for (int i = 0; i < srcSize; ++i) {
    src[i] = stream.ConsumeIntegral<char>();
  }

  // Create a destination buffer
  std::vector<char> dst(LZ4_compressBound(srcSize));

  // Create a LZ4 HC stream
  LZ4_streamHC_t* LZ4_streamHCPtr = LZ4_createStreamHC();
  if (LZ4_streamHCPtr == nullptr) {
    return 0;
  }

  // Perform the compression
  int targetDestSize = LZ4_compressBound(srcSize);
  int result = LZ4_compress_HC_continue_destSize(LZ4_streamHCPtr, src.data(), dst.data(), &srcSize, targetDestSize);

  // Clean up
  LZ4_freeStreamHC(LZ4_streamHCPtr);

  return 0;
}