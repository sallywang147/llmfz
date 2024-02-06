#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "freetype/LzwFuzzTarget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  freetype::LzwFuzzTarget fuzzTarget;
  
  return 0;
}