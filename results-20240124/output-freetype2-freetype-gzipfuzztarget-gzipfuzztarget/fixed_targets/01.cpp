 #include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "freetype/freetype.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();

  freetype::GzipFuzzTarget target(buffer.data(), buffer.size());
  target.GzipFuzzTarget(&target);
  return 0;
}