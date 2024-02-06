#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "vivo_exporter.h"

extern "C" {
#include "flb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* listen = strdup(stream.ConsumeRemainingBytesAsString().c_str());
  const int tcp_port = stream.ConsumeIntegral<int>();
  struct flb_config config;
  struct vivo_exporter ctx;
  vivo_http_server_create(&ctx, listen, tcp_port, &config);
  free(listen);
  vivo_http_server_destroy(&ctx);
  return 0;
}
```

The original code has a memory leak issue because it doesn't call `vivo_http_server_destroy` to free the resources allocated by `vivo_http_server_create`. To fix this issue, we need to call `vivo_http_server_destroy` before returning from the `LLVMFuzzerTestOneInput` function.

The corrected code is shown above.