#include <fuzzer/FuzzedDataProvider.h>
#include "ns_turn_ioaddr.h"
#include "ns_turn_msg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stun_buffer buf;
  union ioa_addr peer_addr;
  short channel_number = stream.ConsumeIntegral<short>();

  // Initialize the buffer
  buf.buf = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();
  buf.len = size;

  // Initialize the peer address
  peer_addr.s4.sin_family = AF_INET;
  peer_addr.s4.sin_addr.s_addr = stream.ConsumeIntegral<uint32_t>();
  peer_addr.s4.sin_port = stream.ConsumeIntegral<uint16_t>();

  stun_set_channel_bind_request(&buf, &peer_addr, channel_number);

  return 0;
}