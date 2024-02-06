#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "brunsli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the InternalState object
  brunsli::internal::dec::InternalState state;

  // Call the destructor of InternalState
  state.~InternalState();

  return 0;
}