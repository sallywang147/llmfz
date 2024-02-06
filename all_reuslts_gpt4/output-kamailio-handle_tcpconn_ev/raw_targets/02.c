#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tcp_connection.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize tcp_connection struct
  struct tcp_connection tcpconn = {0};

  // Consume data for tcp_connection struct
  tcpconn.state = stream.ConsumeIntegral<int>();
  tcpconn.fd = stream.ConsumeIntegral<int>();
  tcpconn.id = stream.ConsumeIntegral<int>();
  tcpconn.type = stream.ConsumeIntegral<int>();
  tcpconn.flags = stream.ConsumeIntegral<int>();
  tcpconn.timeout = stream.ConsumeIntegral<int>();
  tcpconn.send_flags = stream.ConsumeIntegral<int>();
  tcpconn.recv_flags = stream.ConsumeIntegral<int>();

  // Consume data for remaining parameters
  short ev = stream.ConsumeIntegral<short>();
  int fd_i = stream.ConsumeIntegral<int>();

  // Call the target function
  handle_tcpconn_ev(&tcpconn, ev, fd_i);

  return 0;
}