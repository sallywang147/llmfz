#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "StartTcpServer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int PortNumber = stream.ConsumeIntegral<int>();
  int PortNumberPlatform = stream.ConsumeIntegral<int>();

  StartTcpServer(&PortNumber, &PortNumberPlatform);

  return 0;
}