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

The issue in the code was that the `dns.h` header file was not wrapped with `extern "C" {}`. This caused the linker to not be able to find the definitions of the functions declared in the header file. To fix this, the `#include "dns.h"` line was wrapped with `extern "C" {}`.