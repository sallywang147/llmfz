#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" {
#include "mongoose.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  const std::string url = stream.ConsumeRemainingBytesAsString();
  mg_ws_connect(&mgr, url.c_str(), nullptr, nullptr, nullptr);
  mg_mgr_free(&mgr);
  return 0;
}
```

In this case, the error is:
```
error: undefined reference to 'mg_ws_connect'
```

This error is caused by the fact that the `mg_ws_connect` function is declared in the `mongoose.h` header file, but it is not defined in any of the object files that are linked together to create the final executable.

To fix this error, you need to make sure that the `mongoose.c` file, which contains the definition of the `mg_ws_connect` function, is compiled and linked into your program.

You can do this by adding the following line to your `CMakeLists.txt` file:

```
add_executable(my_program main.cpp mongoose.c)
```

This will tell CMake to compile both `main.cpp` and `mongoose.c` and link them together to create the `my_program` executable.

Once you have done this, you should be able to build and run your program without any errors.