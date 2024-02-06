#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder *decoder = new brunsli::BrunsliDecoder();
  decoder->BrunsliDecoder(decoder);
  delete decoder;
  return 0;
}