 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "h2o.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int quality = stream.ConsumeIntegralInRange<int>(0, 11);
  size_t window_bits = stream.ConsumeIntegralInRange<size_t>(10, 24);
  size_t block_bits = stream.ConsumeIntegralInRange<size_t>(10, 24);
  h2o_compress_brotli_open(nullptr, quality, window_bits, block_bits);
  return 0;
}