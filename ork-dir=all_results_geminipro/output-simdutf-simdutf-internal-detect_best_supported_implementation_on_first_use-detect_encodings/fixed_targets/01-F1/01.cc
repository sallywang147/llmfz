#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "simdutf/public/simdutf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();

  simdutf::detect_best_supported_implementation_on_first_use::detect_encodings(
      nullptr, reinterpret_cast<char*>(const_cast<char*>(text.c_str())), text.size());
  return 0;
}
```

Changes made:

- Included the necessary header `simdutf/public/simdutf.h` to use the `simdutf` library.
- Changed the `#include` directive for `simdutf/internal/detect_best_supported_implementation_on_first_use.h` to use the public header instead.
- Removed the unnecessary `extern "C"` wrapper around the `#include` directive for `simdutf/public/simdutf.h` since it is already a C header.