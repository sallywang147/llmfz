#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "dns.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dns_zt* zt = dns_zt_create(nullptr, nullptr);
  if (zt == nullptr) {
    return 0;
  }

  struct dns_view* view = dns_view_create();
  if (view == nullptr) {
    dns_zt_free(zt);
    return 0;
  }

  const bool freeze = stream.ConsumeBool();
  dns_zt_freezezones(zt, view, freeze);

  dns_view_delete(view);
  dns_zt_free(zt);
  return 0;
}
```

The following changes were made to the original code:

1. The header file `dns.h` is now wrapped with `extern "C" {}`. This ensures that the function declarations in the header file are visible to the C++ compiler.
2. The function `dns_zt_freezezones` is now declared in the header file `dns.h`. This allows the C++ compiler to find the function definition when it is called in the `LLVMFuzzerTestOneInput` function.

With these changes, the code should now compile and run without errors.