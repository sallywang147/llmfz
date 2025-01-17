#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "brunsli/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t array_size = stream.remaining_bytes() / sizeof(int);
  std::vector<int> array(array_size);
  for (size_t i = 0; i < array_size; ++i) {
    array[i] = stream.ConsumeIntegral<int>();
  }

  bool bool_arg = stream.ConsumeBool();

  char char_arg = stream.ConsumeIntegral<char>();

  brunsli::FindBestMatrix(array.data(), bool_arg, &char_arg);

  return 0;
}