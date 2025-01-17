#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "simdutf/public/simdutf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  simdutf::detect_best_supported_implementation_on_first_use::count_utf8(
      nullptr, const_cast<char*>(text.c_str()), text.size());
  return 0;
}
```

The original code had the following issues:

* The `simdutf/utf8.h` header was included without being wrapped in `extern "C" {}`. This caused a linker error because the C++ compiler generated name-mangled symbols for the functions and variables declared in that header, while the C compiler expected them to have unmangled names.
* The `simdutf::internal::detect_best_supported_implementation_on_first_use::count_utf8` function was not declared as `extern "C"`, which also caused a linker error because the C compiler expected it to have an unmangled name.

The fixed code wraps the `simdutf/utf8.h` header in `extern "C" {}` and declares the `simdutf::internal::detect_best_supported_implementation_on_first_use::count_utf8` function as `extern "C"`, which allows the C compiler to link to it successfully.