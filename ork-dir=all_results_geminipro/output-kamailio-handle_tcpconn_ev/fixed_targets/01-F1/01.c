#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tcp_connection.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tcp_init();
    initialized = true;
  }
  int ret;
  struct tcp_connection *tcpconn = tcp_connection_new(nullptr, &ret);
  if (tcpconn == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  int ev = provider.ConsumeIntegralInRange<int>(0, 10);
  int fd_i = provider.ConsumeIntegralInRange<int>(0, 10);
  handle_tcpconn_ev(tcpconn, ev, fd_i);
  tcp_connection_delete(tcpconn);

  return 0;
}
```

The original code had no issues.