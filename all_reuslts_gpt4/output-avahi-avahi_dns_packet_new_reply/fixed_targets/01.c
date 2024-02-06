#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/defs.h"
#include "avahi-common/dns-srv-rr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int mtu = stream.ConsumeIntegral<int>();
  int copy_queries = stream.ConsumeBool();
  int aa = stream.ConsumeBool();

  struct AvahiDnsPacket *p = avahi_dns_packet_new(0);
  if (!p) {
    return 0;
  }

  struct AvahiDnsPacket *reply = avahi_dns_packet_new_reply(p, mtu, copy_queries, aa);

  avahi_dns_packet_free(p);
  avahi_dns_packet_free(reply);

  return 0;
}