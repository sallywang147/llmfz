#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include "lwip/ip4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  short short_arg = stream.ConsumeIntegral<short>();

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<char> char_vector = stream.ConsumeBytes<char>(stream.remaining_bytes());
  char* char_ptr = char_vector.data();

  // User defined objects
  struct udp_pcb udp_pcb_obj;
  struct pbuf pbuf_obj;
  struct ip4_addr ip4_addr_obj;

  // Call the function with the fuzzed inputs
  udp_recv_proc(char_ptr, &udp_pcb_obj, &pbuf_obj, &ip4_addr_obj, short_arg);

  return 0;
}