#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "easywsclient.hpp"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "easywsclient.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string str(reinterpret_cast<const char *>(data), size);
  easywsclient::WebSocket::from_url(str);
  return 0;
}
```

The original code has a build error because the `from_url_no_mask` function is not defined in the `easywsclient.h` header. To fix this, we need to use the `from_url` function instead, which is defined in the header.