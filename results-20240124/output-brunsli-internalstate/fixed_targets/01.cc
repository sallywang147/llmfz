#include <brunsli/brunsli_decode.h>
#include "../dec/state.h"

extern "C" {
#include <brunsli/brunsli_decode.h>
#include "../dec/state.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::internal::dec::State state;
  brunsli::Status status = brunsli::Init(&state);
  if (status != brunsli::BRUNSLI_OK) return 0;
  state.data = data;
  state.pos = 0;
  state.len = size;
  status = brunsli::Decode(&state);
  // Add this line to call the destructor.
  brunsli::Cleanup(&state);
  return 0;
}
}  // extern "C"