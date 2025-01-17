#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lwip/udp.h"
#include "lwip/ip4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize the required parameters for udp_recv_proc
  char arg1 = provider.ConsumeIntegral<char>();
  struct udp_pcb arg2;
  struct pbuf arg3;
  struct ip4_addr arg4;
  short arg5 = provider.ConsumeIntegral<short>();

  // Call the function to fuzz
  udp_recv_proc(&arg1, &arg2, &arg3, &arg4, arg5);

  return 0;
}