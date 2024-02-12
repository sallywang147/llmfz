 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <string>

#include "freetype/gziptarget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  freetype::GzipFuzzTarget target;
  target.GzipFuzzTarget(&target);
  return 0;
}