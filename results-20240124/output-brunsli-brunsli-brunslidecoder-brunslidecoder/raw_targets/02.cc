 #include <brunsli/brunsli_decode.h>
#include <brunsli/types.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  brunsli::BrunsliDecoder decoder;
  brunsli::BrunsliDecoder *dec = &decoder;
  brunsli::BrunsliDecoder::BrunsliDecoder(dec);
  return 0;
}