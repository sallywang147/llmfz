#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "dnserv.h"

// Dummy function to be passed as a parameter to dnserv_init
void dummy_func() {
    return;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ip4_addr ip;
  ip.addr = stream.ConsumeIntegral<uint32_t>();
  
  short port = stream.ConsumeIntegral<short>();

  func_type function = &dummy_func;

  dnserv_init(&ip, port, &function);

  return 0;
}