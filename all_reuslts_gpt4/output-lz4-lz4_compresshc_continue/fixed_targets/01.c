#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lz4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static LZ4_streamHC_t* const lz4_stream = LZ4_createStreamHC();
  if (lz4_stream == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  const std::string src = stream.ConsumeRandomLengthString();
  const int max_dst_size = LZ4_compressBound(src.size());
  if (max_dst_size <= 0) {
    return 0;
  }
  std::vector<char> dst(max_dst_size);
  
  LZ4_compressHC_continue(lz4_stream, const_cast<char*>(src.data()), dst.data(), src.size());
  
  return 0;
}