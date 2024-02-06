#include <fuzzer/FuzzedDataProvider.h>
#include "../forward.h"
#include "../ip_addr.h"
#include "../parser/msg_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);

  struct sip_msg msg = {};
  struct proxy_l dest = {};

  // Extract data for `msg` and `dest`
  msg.buf = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2).c_str();
  msg.len = strlen(msg.buf);

  dest.port = stream.ConsumeIntegral<unsigned short>();
  dest.proto = stream.ConsumeIntegral<unsigned short>();
  dest.addr_idx = stream.ConsumeIntegral<unsigned int>();
  dest.flags = stream.ConsumeIntegral<unsigned int>();

  // Call the function to fuzz
  w_forward(&msg, &dest);

  return 0;
}