#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "StartTcpServer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int port_number = stream.ConsumeIntegral<int>();
  int port_number_platform = stream.ConsumeIntegral<int>();
  StartTcpServer(&port_number, &port_number_platform);
  return 0;
}