#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Platform.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int port_number = provider.ConsumeIntegral<int>();
  int port_number_platform = provider.ConsumeIntegral<int>();
  StartTcpServer(&port_number, &port_number_platform);
  return 0;
}