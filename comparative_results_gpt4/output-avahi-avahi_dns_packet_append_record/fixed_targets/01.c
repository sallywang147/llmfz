#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/dns.h"
#include "avahi-common/domain.h"
#include "avahi-common/malloc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize AvahiDnsPacket
    AvahiDnsPacket *p = avahi_dns_packet_new(0);

    // Initialize AvahiRecord
    AvahiRecord *r = avahi_new(AvahiRecord, 1);
    r->clazz = AVAHI_DNS_CLASS_IN;
    r->type = AVAHI_DNS_TYPE_A;
    r->ttl = stream.ConsumeIntegral<uint32_t>();
    r->data.a.address = stream.ConsumeIntegral<uint32_t>();

    // Consume cache_flush and max_ttl from the data provider
    int cache_flush = stream.ConsumeIntegral<int>();
    int max_ttl = stream.ConsumeIntegral<int>();

    // Call the function to fuzz
    avahi_dns_packet_append_record(p, r, cache_flush, max_ttl);

    // Free allocated memory
    avahi_free(r);
    avahi_dns_packet_free(p);

    return 0;
}