#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct ip4_addr addr;
  provider.ConsumeBytes(&addr, sizeof(addr));
  short port = provider.ConsumeIntegral<short>();
  func_type func = (func_type)provider.ConsumeIntegral<uint32_t>();
  char result = dnserv_init(&addr, port, func);
  return result;
}