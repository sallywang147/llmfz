 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "freetype/lzw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  freetype::LzwFuzzTarget target;

  const uint8_t* input = stream.ConsumeRemainingBytes<uint8_t>();
  const size_t input_size = stream.remaining_bytes();
  target.LzwFuzzTarget(&target, input, input_size);

  return 0;
}