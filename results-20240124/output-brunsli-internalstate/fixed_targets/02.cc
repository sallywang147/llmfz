#include <brunsli/types.h>
#include "../dec/state.h"

extern "C" {
#include "../dec/decode.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::internal::dec::InternalState* state = new brunsli::internal::dec::InternalState;
  delete state;
  return 0;
}