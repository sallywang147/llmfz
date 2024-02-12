#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "ssh.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t packet_type = stream.ConsumeIntegral<uint8_t>();
  const uint32_t packet_length = stream.ConsumeIntegral<uint32_t>();
  const std::string username = stream.ConsumeRemainingBytesAsString();

  ssh_packet packet;
  packet.type = packet_type;
  packet.length = packet_length;
  packet.data = reinterpret_cast<uint8_t*>(const_cast<char*>(username.c_str()));
  packet.data_len = username.size();

  recv_msg_userauth_pk_ok(&packet);

  return 0;
}