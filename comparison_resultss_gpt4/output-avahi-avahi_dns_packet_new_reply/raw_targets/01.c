#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/dns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dummy AvahiDnsPacket
  struct AvahiDnsPacket *p = avahi_dns_packet_new(0);

  // Extract parameters for avahi_dns_packet_new_reply
  int mtu = stream.ConsumeIntegral<int>();
  int copy_queries = stream.ConsumeIntegral<int>();
  int aa = stream.ConsumeIntegral<int>();

  // Call the function
  struct AvahiDnsPacket *reply_packet = avahi_dns_packet_new_reply(p, mtu, copy_queries, aa);

  // Clean up
  avahi_dns_packet_free(p);
  if (reply_packet != nullptr) {
    avahi_dns_packet_free(reply_packet);
  }

  return 0;
}