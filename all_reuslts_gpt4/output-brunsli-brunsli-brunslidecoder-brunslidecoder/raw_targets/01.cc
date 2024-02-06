#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "brunsli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a BrunsliDecoder instance
  brunsli::BrunsliDecoder decoder;

  // Create another BrunsliDecoder instance using the first one
  brunsli::BrunsliDecoder decoder2(&decoder);

  return 0;
}