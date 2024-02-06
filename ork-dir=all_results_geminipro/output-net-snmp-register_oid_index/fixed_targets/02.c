#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "oid_index.h"  // Include the header file that defines `register_oid_index`
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t name_len = stream.ConsumeIntegral<size_t>();
  const size_t value_len = stream.ConsumeIntegral<size_t>();

  std::vector<size_t> name;
  std::vector<size_t> value;

  for (size_t i = 0; i < name_len; ++i) {
    name.push_back(stream.ConsumeIntegral<size_t>());
  }

  for (size_t i = 0; i < value_len; ++i) {
    value.push_back(stream.ConsumeIntegral<size_t>());
  }

  register_oid_index(name.data(), name_len, value.data(), value_len);

  return 0;
}
```

The following changes were made:

* The header file `oid_index.h` is included within an `extern "C" {}` block. This is necessary because the function `register_oid_index` is defined in a C file, and the C++ compiler needs to be told that it is a C function.
* The function `register_oid_index` is declared with `extern "C"`. This is also necessary because the function is defined in a C file.

With these changes, the code should build successfully.