#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "dnserv.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct ip4_addr ip;
  ip.addr = provider.ConsumeIntegral<uint32_t>();

  short port = provider.ConsumeIntegral<short>();

  func_type func = (func_type)provider.ConsumeIntegral<uint32_t>();

  char ret = dnserv_init(&ip, port, func);

  return 0;
}