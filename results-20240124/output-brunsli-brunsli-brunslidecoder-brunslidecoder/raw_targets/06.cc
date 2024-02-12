 #include <brunsli/brunsli_decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  decoder.BrunsliDecoder(&decoder);
  return 0;
}