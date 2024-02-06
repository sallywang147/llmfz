#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "png.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* input_cstr = const_cast<char*>(input.c_str());
  png_image_read_direct(input_cstr);
  return 0;
}
```

In this code, the `#include "png.h"` directive is wrapped with `extern "C" {}` to fix the linking error. This is necessary because the `png.h` header file contains C-style function declarations, which are not compatible with C++ function declarations by default. The `extern "C"` directive tells the compiler to treat the included header file as a C header file, which allows the C-style function declarations to be used in the C++ code.