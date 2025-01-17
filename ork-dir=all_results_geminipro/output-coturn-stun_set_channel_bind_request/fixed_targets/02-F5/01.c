#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "stun_buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stun_buffer* buf = stun_buffer_new();
  if (!buf)
    return 0;

  union ioa_addr peer_addr;
  peer_addr.ipv4.s_addr = stream.ConsumeIntegral<uint32_t>();
  peer_addr.ipv6.s6_addr[0] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[1] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[2] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[3] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[4] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[5] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[6] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[7] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[8] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[9] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[10] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[11] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[12] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[13] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[14] = stream.ConsumeIntegral<uint8_t>();
  peer_addr.ipv6.s6_addr[15] = stream.ConsumeIntegral<uint8_t>();

  short channel_number = stream.ConsumeIntegral<short>();

  short ret = stun_set_channel_bind_request(buf, &peer_addr, channel_number);
  if (ret < 0)
    return 0;

  stun_buffer_free(buf);
  return 0;
}