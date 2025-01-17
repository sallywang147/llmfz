#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "freetype/lzw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> input = stream.ConsumeRemainingBytes();
  freetype::LzwFuzzTarget target(input.data(), input.size());
  target.LzwFuzzTarget(&target);
  return 0;
}