#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-core/dns.h"
#include "avahi-common/rr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an AvahiDnsPacket
  struct AvahiDnsPacket *p = avahi_dns_packet_new(0, 0, 0, 0, 0);
  if (!p) {
    return 0;
  }

  // Create an AvahiRecord
  struct AvahiRecord *r = avahi_record_new_full("example.com", AVAHI_DNS_CLASS_IN, AVAHI_DNS_TYPE_A, 3600);
  if (!r) {
    avahi_dns_packet_free(p);
    return 0;
  }

  // Extract cache_flush and max_ttl
  int cache_flush = stream.ConsumeIntegral<int>();
  int max_ttl = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  avahi_dns_packet_append_record(p, r, cache_flush, max_ttl);

  // Clean up
  avahi_record_unref(r);
  avahi_dns_packet_free(p);

  return 0;
}