#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder decoder;
  size_t out_size = 0;
  uint8_t* out = nullptr;
  size_t meta_size = 0;
  char* meta = nullptr;
  decoder.Decode(&out_size, &out, &meta_size, &meta, &stream);
  return 0;
}