#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "TcpServer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int port_number = 0;
  int port_number_platform = 0;
  StartTcpServer(&port_number, &port_number_platform);
  return 0;
}