#include <fuzzer/FuzzedDataProvider.h>
#include <cstring>

extern "C" {
#include "libraw/libraw.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LibRaw raw;
  raw.open_buffer(data, size);

  // Extract an array of bytes as a vector. You MUST call `.data()` to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  const char *data_ptr = reinterpret_cast<const char *>(bytes.data());

  // Call the function to fuzz
  raw.unpack_function_name(data_ptr);

  return 0;
}
```

The issue in the original code was that the `unpack_function_name` function takes a `const char *` argument, but the code was passing a `char *` argument. This caused a compiler error because the function signature did not match the function call.

To fix the issue, the code was changed to pass a `const char *` argument to the `unpack_function_name` function. This was done by casting the `data_ptr` variable to a `const char *` using the `(const char *)` cast.

With this change, the code should now compile and run without errors.