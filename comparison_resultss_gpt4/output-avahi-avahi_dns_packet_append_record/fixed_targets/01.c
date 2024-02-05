#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/dns.h"
#include "avahi-common/malloc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct AvahiDnsPacket *p = avahi_dns_packet_new(0, 0, 0);
    if (!p) {
        return 0;
    }

    struct AvahiRecord *r = avahi_new(struct AvahiRecord, 1);
    if (!r) {
        avahi_dns_packet_free(p);
        return 0;
    }

    r->key = avahi_new(AvahiKey, 1);
    if (!r->key) {
        avahi_free(r);
        avahi_dns_packet_free(p);
        return 0;
    }

    r->key->name = avahi_strdup("www.example.com");
    r->key->clazz = AVAHI_DNS_CLASS_IN;
    r->key->type = AVAHI_DNS_TYPE_A;
    r->data.a.address = stream.ConsumeIntegral<uint32_t>();
    r->ttl = stream.ConsumeIntegral<uint32_t>();
    r->flags = stream.ConsumeIntegral<uint16_t>();

    int cache_flush = stream.ConsumeIntegral<int>();
    int max_ttl = stream.ConsumeIntegral<int>();

    avahi_dns_packet_append_record(p, r, cache_flush, max_ttl);

    avahi_free(r->key->name);
    avahi_free(r->key);
    avahi_free(r);
    avahi_dns_packet_free(p);

    return 0;
}