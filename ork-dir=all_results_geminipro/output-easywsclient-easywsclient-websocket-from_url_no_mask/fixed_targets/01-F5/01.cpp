#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <string>

#include "easywsclient.hpp"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "easywsclient.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string str(reinterpret_cast<const char *>(data), size);
  easywsclient::WebSocket::from_url_no_mask(str);
  return 0;
}
```

Changes made:

1. Added `#include <string>` to include the necessary header for the `std::string` class.
2. Wrapped the `#include "easywsclient.h"` directive with `extern "C" {}` to resolve the linker error caused by different name mangling conventions between C and C++.