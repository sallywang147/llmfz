#include <brunsli/brunsli_decode.h>

extern "C" {
#include <brunsli/brunsli_dictionary.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  int x;
  bool y;
  char z[size];
  brunsli::FindBestMatrix(&x, y, z);
  return 0;
}