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
  struct tcp_connection tcpconn;
  tcpconn.state = stream.ConsumeIntegral<int>();
  tcpconn.fd = stream.ConsumeIntegral<int>();
  tcpconn.id = stream.ConsumeIntegral<int>();
  tcpconn.local_port = stream.ConsumeIntegral<int>();
  tcpconn.remote_port = stream.ConsumeIntegral<int>();
  tcpconn.timeout = stream.ConsumeIntegral<int>();
  tcpconn.flags = stream.ConsumeIntegral<int>();

  // Generate short event
  short ev = stream.ConsumeIntegral<short>();

  // Generate file descriptor index
  int fd_i = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  handle_tcpconn_ev(&tcpconn, ev, fd_i);

  return 0;
}