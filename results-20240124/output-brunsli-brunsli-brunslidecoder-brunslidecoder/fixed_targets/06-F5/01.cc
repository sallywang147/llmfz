#include <brunsli/brunsli_decode.h>

extern "C" {
#include <brunsli/brunsli_decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  decoder.Init(&decoder, data, size);
  return 0;
}