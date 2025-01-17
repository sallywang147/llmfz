#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "brunsli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::internal::dec::InternalState* state = new brunsli::internal::dec::InternalState();

  // Your code here to initialize and use the state...

  // Call the destructor explicitly.
  state->~InternalState();

  return 0;
}