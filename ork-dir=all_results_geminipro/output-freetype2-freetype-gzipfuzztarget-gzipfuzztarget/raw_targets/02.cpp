#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "freetype/gzip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  freetype::GzipFuzzTarget fuzz_target;
  new (&fuzz_target) freetype::GzipFuzzTarget();
  fuzz_target.GzipFuzzTarget(&fuzz_target);
  return 0;
}