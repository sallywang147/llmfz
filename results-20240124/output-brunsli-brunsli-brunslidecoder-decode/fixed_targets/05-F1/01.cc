#include <brunsli/brunsli_decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  size_t decoded_size;
  char* decoded_data;
  int status = decoder.Decode(data, size, &decoded_size, &decoded_data);
  return status;
}