#include <fuzzer/FuzzedDataProvider.h>
#include <lz4.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // We need at least one byte for compression level
  if (size < 1) {
    return 0;
  }

  // Use the first byte of the input data as the compression level
  int compressionLevel = stream.ConsumeIntegralInRange<int>(1, 16);

  // Use the rest of the input data as the source data to compress
  std::string src = stream.ConsumeRemainingBytesAsString();
  int srcSize = src.size();

  // The destination buffer must be large enough to hold the compressed data
  // LZ4_compressBound provides the maximum size that LZ4 compression may output in a "worst case" scenario
  int maxDstSize = LZ4_compressBound(srcSize);
  std::vector<char> dst(maxDstSize);

  LZ4_compressHC2(src.data(), dst.data(), srcSize, compressionLevel);

  return 0;
}