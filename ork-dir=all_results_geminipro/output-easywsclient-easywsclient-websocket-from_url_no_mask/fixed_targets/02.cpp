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
  easywsclient::WebSocket::from_url(str);  // Use from_url instead of from_url_no_mask
  return 0;
}
```

In the fixed code, we replaced the `from_url_no_mask` function with the `from_url` function, which is defined in the `easywsclient.h` header. This should resolve the build error.