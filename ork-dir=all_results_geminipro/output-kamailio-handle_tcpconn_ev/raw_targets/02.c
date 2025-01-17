#include <fuzzer/FuzzedDataProvider.h>
#include <netinet/in.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

int handle_tcpconn_ev(struct tcp_connection * tcpconn, short ev, int fd_i) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct tcp_connection tcpconn;
  tcpconn.fd = provider.ConsumeIntegral<int>();
  tcpconn.fd_i = provider.ConsumeIntegral<int>();
  tcpconn.fd_o = provider.ConsumeIntegral<int>();
  tcpconn.fd_e = provider.ConsumeIntegral<int>();
  tcpconn.flags = provider.ConsumeIntegral<int>();
  tcpconn.state = provider.ConsumeIntegral<int>();
  tcpconn.timeout = provider.ConsumeIntegral<int>();
  tcpconn.last_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_tx = provider.ConsumeIntegral<int>();
  tcpconn.last_rx = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity = provider.ConsumeIntegral<int>();
  tcpconn.last_rx_activity =