#include "../common/platform.h"
#include "../dec/internal_state.h"
#include <brunsli/brunsli_decode.h>
#include <brunsli/status.h>
#include <brunsli/types.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  brunsli::internal::dec::InternalState* state = new brunsli::internal::dec::InternalState();
  brunsli::BrunsliStatus status = brunsli::BrunsliDecode(data, size, state);
  if (status == brunsli::BRUNSLI_OK) {
    delete state;
  }
  return 0;
}