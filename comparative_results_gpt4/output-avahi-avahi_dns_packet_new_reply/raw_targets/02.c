#include <fuzzer/FuzzedDataProvider.h>
#include "avahi-core/dns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  struct AvahiDnsPacket *p = avahi_dns_packet_new(0, 0, 0);
  if (!p) {
    return 0;
  }

  int mtu = fuzzed_data.ConsumeIntegral<int>();
  int copy_queries = fuzzed_data.ConsumeIntegral<int>();
  int aa = fuzzed_data.ConsumeIntegral<int>();

  struct AvahiDnsPacket *reply = avahi_dns_packet_new_reply(p, mtu, copy_queries, aa);

  avahi_dns_packet_free(p);
  if (reply) {
    avahi_dns_packet_free(reply);
  }
  
  return 0;
}