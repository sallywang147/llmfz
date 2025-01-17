#include <fuzzer/FuzzedDataProvider.h>

#include "nxt_main.h"

extern "C" {
#include "nxt_memzero.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(struct nxt_port_recv_msg_s)) {
    return 0;
  }

  struct nxt_task_s task;
  nxt_memzero(&task, sizeof(struct nxt_task_s));

  struct nxt_port_recv_msg_s msg;
  nxt_memzero(&msg, sizeof(struct nxt_port_recv_msg_s));

  FuzzedDataProvider provider(data, size);
  provider.ConsumeBytes<uint8_t>(&msg, sizeof(struct nxt_port_recv_msg_s));

  nxt_main_port_modules_handler(&task, &msg);

  return 0;
}
```

The build issue in this case is caused by the missing declaration of the `nxt_memzero` function. To fix this, the header file `nxt_memzero.h` needs to be included and wrapped with `extern "C" {}`. This is because the `nxt_memzero` function is declared in a C header file, and the C++ compiler needs to be explicitly told that it is a C function.