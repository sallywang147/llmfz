#include <brunsli/brunsli_decode.h>
#include <brunsli/dec/state.h>
#include <brunsli/types.h>

extern "C" {
#include <brunsli/dec/decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::internal::dec::InternalState state;
  state.~InternalState(&state);
  return 0;
}