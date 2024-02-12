 #include <brunsli/brunsli_decode.h>
#include "../dec/state.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::internal::dec::InternalState* state =
      new brunsli::internal::dec::InternalState();
  brunsli::BrunsliStatus status = brunsli::BrunsliInit(state);
  if (status != brunsli::BRUNSLI_OK) return 0;
  state->data = data;
  state->pos = 0;
  state->len = size;
  status = brunsli::BrunsliDecode(state);
  delete state;
  return 0;
}