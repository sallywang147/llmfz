#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "lodepng.h"

extern "C" {
#include <png.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  const std::vector<uint8_t> image = stream.ConsumeRemainingBytes();
  const int width = stream.ConsumeIntegral<int>();
  const int height = stream.ConsumeIntegral<int>();

  lodepng_encode32_file(filename.c_str(), reinterpret_cast<char*>(image.data()),
                         width, height);
  return 0;
}
```

In this case, the build error is caused by the missing `png.h` header, which is required for the `lodepng_encode32_file` function. To fix this, we need to include the `png.h` header and wrap it with `extern "C" {}` to ensure that the C++ compiler doesn't mangle the function names.