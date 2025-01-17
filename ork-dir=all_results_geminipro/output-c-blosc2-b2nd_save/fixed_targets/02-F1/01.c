#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "b2nd.h"

extern "C" {
#include "b2nd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate a random b2nd_array_t struct.
  b2nd_array_t array;
  array.dim = provider.ConsumeIntegralInRange<int>(1, 10);
  array.size = provider.ConsumeIntegralInRange<size_t>(1, 10000);
  array.data = provider.ConsumeBytes<uint8_t>(array.size);

  // Generate a random file name.
  std::string file_name = provider.ConsumeRandomLengthString(10);

  // Call b2nd_save to save the array to a file.
  int result = b2nd_save(&array, file_name.c_str());
  if (result != 0) {
    // An error occurred while saving the array.
    return 0;
  }

  // Clean up the temporary file.
  remove(file_name.c_str());

  return 0;
}
```

The build issues were caused by the following:

* The header `b2nd.h` was not wrapped with `extern "C" {}`. This caused the linker to be unable to find the definition of the `b2nd_save` function.
* The `b2nd.h` header was not included in the `extern "C" {}` block. This caused the compiler to be unable to find the definition of the `b2nd_array_t` struct.

To fix these issues, the `b2nd.h` header was wrapped with `extern "C" {}` and the `b2nd.h` header was included in the `extern "C" {}` block.