#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "lz4.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  const size_t dst_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  const int c_level = stream.ConsumeIntegralInRange<int>(0, 16);
  char* src = new char[src_size];
  char* dst = new char[dst_size];
  stream.ConsumeBytes(src, src_size);
  const int result = LZ4_compressHC2(src, dst, src_size, c_level);
  delete[] src;
  delete[] dst;
  return result;
}