#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/dns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int mtu = stream.ConsumeIntegral<int>();
  int copy_queries = stream.ConsumeIntegral<int>();
  int aa = stream.ConsumeIntegral<int>();

  size_t remaining_bytes = stream.remaining_bytes();
  if (remaining_bytes == 0) {
    return 0;
  }
  std::vector<uint8_t> packet_data = stream.ConsumeRemainingBytes<uint8_t>();
  
  struct AvahiDnsPacket *p = avahi_dns_packet_new(packet_data.size());
  if (p == nullptr) {
    return 0;
  }
  memcpy(p->data, packet_data.data(), packet_data.size());

  struct AvahiDnsPacket *reply = avahi_dns_packet_new_reply(p, mtu, copy_queries, aa);
  if (reply != nullptr) {
    avahi_dns_packet_free(reply);
  }

  avahi_dns_packet_free(p);

  return 0;
}