#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/domain.h"
#include "avahi-common/malloc.h"
#include "avahi-core/dns.h"
#include "avahi-core/domain-util.h"
#include "avahi-core/log.h"
#include "avahi-core/service.h"  // Include the header file that declares avahi_service_name_split

extern "C" {
#include "avahi-core/service.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

void domain_ends_with_mdns_suffix(const char *domain) {
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_LOCAL);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV4);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV6);
}

bool copy_rrs(AvahiDnsPacket *from, AvahiDnsPacket *to, unsigned idx) {
  for (uint16_t n = avahi_dns_packet_get_field(from, idx); n > 0; n--) {
    AvahiRecord *record;
    int cache_flush = 0;
    uint8_t *res;

    if (!(record = avahi_dns_packet_consume_record(from, &cache_flush)))
      return false;

    avahi_free(avahi_record_to_string(record));

    domain_ends_with_mdns_suffix(record->key->name);

    // This resembles the RR callbacks responsible for browsing services
    if (record->key->type == AVAHI_DNS_TYPE_PTR) {
      char service[AVAHI_LABEL_MAX], type[AVAHI_DOMAIN_NAME_MAX], domain[AVAHI_DOMAIN_NAME_MAX];
      char name[AVAHI_DOMAIN_NAME_MAX];
      int res;

      if (avahi_service_name_split(record->data.ptr.name, service, sizeof(service), type, sizeof(type), domain, sizeof(domain)) >= 0) {
        res = avahi_service_name_join(name, sizeof(name), service, type, domain);
        assert(res >= 0);
      }

      if (avahi_service_name_split(record->data.ptr.name, NULL, 0, type, sizeof(type), domain, sizeof(domain)) >= 0) {
        res = avahi_service_name_join(name, sizeof(name), NULL, type, domain);
        assert(res >= 0);
      }
    }

    res = avahi_dns_packet_append_record(to, record, cache_flush, 0);
    avahi_record_unref(record);
    if (!res)
      return false;
    avahi_dns_packet_inc_field(to, idx);
  }
  return true;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiDnsPacket *p1 = NULL, *p2 = NULL;

  if (size > AVAHI_DNS_PACKET_SIZE_MAX)
    return 0;

  avahi_set_log_function(log_function);

  if (!(p1 = avahi_dns_packet_new(size + AVAHI_DNS_PACKET_EXTRA_SIZE)))
    goto finish;

  memcpy(AVAHI_DNS_PACKET_DATA(p1), data, size);
  p1->size = size;

  if (avahi_dns_packet_check_valid(p1) < 0)
    goto finish;

  if (!(p2 = avahi_dns_packet_new_reply(p1, 1500, 1, 1)))
    goto finish;

finish:
  if (p2)
    avahi_dns_packet_free(p2);
  if (p1)
    avahi_dns_packet_free(p1);

  return 0;
}