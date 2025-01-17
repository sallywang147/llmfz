#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd_array.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct b2nd_array_t array;
  b2nd_array_init(&array);

  while (stream.remaining_bytes() > 0) {
    size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    std::string str = stream.ConsumeBytesAsString(str_size);
    char c = stream.ConsumeIntegral<char>();
    size_t pos = stream.ConsumeIntegral<size_t>();

    b2nd_insert(&array, const_cast<char*>(str.c_str()), str_size, c, pos);
  }

  b2nd_array_free(&array);

  return 0;
}