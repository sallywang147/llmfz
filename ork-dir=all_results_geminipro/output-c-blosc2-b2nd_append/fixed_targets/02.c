#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "b2nd.h"

extern "C" {
#include "b2nd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct b2nd_array_t* array = b2nd_array_create(1024);
  if (array == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    std::string str = provider.ConsumeRandomLengthString(len);
    char delimiter = provider.ConsumeIntegral<char>();

    int ret = b2nd_append(array, str.c_str(), len, delimiter);
    if (ret != 0) {
      b2nd_array_destroy(array);
      return 0;
    }
  }

  b2nd_array_destroy(array);

  return 0;
}