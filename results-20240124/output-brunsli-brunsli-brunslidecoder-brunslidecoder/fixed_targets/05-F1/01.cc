#include <brunsli/brunsli_decode.h>
#include "fuzzer/FuzzedDataProvider.h"
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder decoder;
  decoder.BrunsliDecoderInit(&decoder, nullptr, nullptr, nullptr, 0, nullptr,
                                nullptr);
  return 0;
}