#include <brunsli/decode.h>
#include <brunsli/types.h>
#include <brunsli/brunsli_decode.h>
#include "../dec/state.h"

extern "C" {
struct brunsli::internal::dec::InternalState;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliStatus status;
  brunsli::internal::dec::State state;
  brunsli::internal::dec::InternalState internal_state;
  state.internal = &internal_state;

  size_t start = 0;
  for (size_t end = 0; end <= size; ++end) {
    state.data = data + start;
    state.pos = 0;
    state.len = end - start;
    status = brunsli::internal::dec::ProcessJpeg(&state, nullptr);
    brunsli::BrunsliStatus expected_status =
        end < size ? brunsli::BRUNSLI_NOT_ENOUGH_DATA : brunsli::BRUNSLI_OK;
    if (status != expected_status) return 0;
    start += state.pos;
  }

  state.internal->brunsli::internal::dec::InternalState::~InternalState();  // Fix: add the scope resolution operator
  return 0;
}