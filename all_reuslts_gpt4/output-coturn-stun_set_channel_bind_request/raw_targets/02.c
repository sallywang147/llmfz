#include <fuzzer/FuzzedDataProvider.h>
#include "ns_turn_ioaddr.h"
#include "stun_buffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a stun_buffer
  stun_buffer buf;
  buf.len = stream.ConsumeIntegralInRange<int>(0, STUN_BUFFER_SIZE);
  buf.offset = stream.ConsumeIntegralInRange<int>(0, buf.len);
  std::vector<uint8_t> buf_data = stream.ConsumeBytes<uint8_t>(buf.len);
  memcpy(buf.buf, buf_data.data(), buf.len);

  // Create an ioa_addr
  ioa_addr peer_addr;
  peer_addr.ss.sa_family = AF_INET;
  peer_addr.s4.sin_port = stream.ConsumeIntegral<uint16_t>();
  peer_addr.s4.sin_addr.s_addr = stream.ConsumeIntegral<uint32_t>();

  // Get a channel number
  short channel_number = stream.ConsumeIntegral<short>();

  // Call the function
  stun_set_channel_bind_request(&buf, &peer_addr, channel_number);

  return 0;
}