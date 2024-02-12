#include <brunsli/brunsli_decode.h>

extern "C" {
#include <brunsli/decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  brunsli::BrunsliDecoder* decoder_ptr = &decoder;
  brunsli::BrunsliDecoder::BrunsliDecoder(decoder_ptr);
  return 0;
}