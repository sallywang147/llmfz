#include <brunsli/decode.h>
#include <brunsli/types.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  size_t in_size = size;
  const char *in = reinterpret_cast<const char *>(data);
  size_t out_size = 0;
  char *out = nullptr;
  size_t decoded_size = 0;
  char *decoded = nullptr;
  int ret = decoder.Decode(&in_size, &in, &out_size, &out, &decoded_size, &decoded);
  free(out);
  free(decoded);
  return ret;
}