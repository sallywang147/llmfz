#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <brunsli/brunsli_decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder decoder;
  decoder.SetDecoder(&decoder);
  decoder.Decode(stream);
  return 0;
}