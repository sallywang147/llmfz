 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "freetype/lzw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> input = stream.ConsumeRemainingBytes<uint8_t>();

  freetype::LzwFuzzTarget target;
  target.LzwFuzzTarget(&target);
  target.lzw_decode(input.data(), input.size());

  return 0;
}