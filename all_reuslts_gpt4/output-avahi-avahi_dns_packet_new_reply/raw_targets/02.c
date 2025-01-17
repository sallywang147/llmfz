#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/defs.h"
#include "avahi-common/dns-srv-rr.h"
#include "avahi-common/malloc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize AvahiDnsPacket
  struct AvahiDnsPacket *p = avahi_dns_packet_new(0, 0, 0, 0, 0);
  if (!p) {
    return 0;
  }

  // Extract integral values
  int mtu = stream.ConsumeIntegral<int>();
  int copy_queries = stream.ConsumeIntegral<int>();
  int aa = stream.ConsumeIntegral<int>();

  // Call the target function
  struct AvahiDnsPacket *reply_packet = avahi_dns_packet_new_reply(p, mtu, copy_queries, aa);

  // Cleanup
  avahi_dns_packet_free(p);
  if (reply_packet) {
    avahi_dns_packet_free(reply_packet);
  }

  return 0;
}