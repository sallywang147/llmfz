#include <brunsli/brunsli_decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  size_t decoded_size;
  uint8_t* decoded_data;
  size_t available_in = size;
  const uint8_t* next_in = data;
  int status = decoder.Decode(&available_in, &next_in, &decoded_size, &decoded_data);
  free(decoded_data);
  return status;
}