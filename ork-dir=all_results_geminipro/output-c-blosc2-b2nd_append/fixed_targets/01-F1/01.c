#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "b2nd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    b2nd_init();
    initialized = true;
  }
  int ret;
  struct b2nd_array_t* array = b2nd_array_new(&ret);
  if (array == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  size_t array_size = provider.ConsumeIntegralInRange<size_t>(0, 1<<20);
  std::vector<char> array_data(array_size);
  provider.ConsumeBytes(array_data.data(), array_size);

  char delim = provider.ConsumeIntegral<char>();

  b2nd_append(array, array_data.data(), array_size, delim);

  b2nd_array_delete(array);

  return 0;
}
```
In this fixed code, the `#include "b2nd.h"` is wrapped with `extern "C" {}` to resolve the linking issue.