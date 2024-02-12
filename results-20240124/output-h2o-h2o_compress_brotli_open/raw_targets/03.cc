 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "h2o.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t quality = stream.ConsumeIntegralInRange<size_t>(0, 11);
  size_t window_size = stream.ConsumeIntegralInRange<size_t>(10, 24);
  size_t block_size = stream.ConsumeIntegralInRange<size_t>(1, 256);

  h2o_compress_brotli_open(nullptr, quality, window_size, block_size);

  return 0;
}