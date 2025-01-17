#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "lz4hc.h"

extern "C" {
#include "lz4.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* src = new char[src_size];
  stream.ConsumeBytes(src, src_size);

  const size_t dst_size = LZ4_compressBound(src_size);
  char* dst = new char[dst_size];

  const int c_level = stream.ConsumeIntegralInRange<int>(0, 16);
  LZ4_compressHC2(src, dst, src_size, c_level);

  delete[] src;
  delete[] dst;

  return 0;
}