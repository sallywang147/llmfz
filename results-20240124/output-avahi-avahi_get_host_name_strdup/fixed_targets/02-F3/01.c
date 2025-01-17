#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/domain.h"
#include "avahi-common/malloc.h"
#include "avahi-core/dns.h"
#include "avahi-core/domain-util.h"
#include "avahi-core/log.h"

extern "C" {
void log_function(AvahiLogLevel level, const char *txt) {}
AvahiDnsPacket *avahi_dns_packet_new(unsigned int size);
unsigned short avahi_dns_packet_get_field(AvahiDnsPacket *p, unsigned int field);
AvahiRecord *avahi_dns_packet_consume_record(AvahiDnsPacket *p, int *cache_flush);
uint8_t *avahi_dns_packet_append_record(AvahiDnsPacket *p, AvahiRecord *r, int cache_flush, unsigned int flags);
void avahi_dns_packet_inc_field(AvahiDnsPacket *p, unsigned int field);
AvahiKey *avahi_dns_packet_consume_key(AvahiDnsPacket *p, int *unicast_response);
uint8_t *avahi_dns_packet_append_key(AvahiDnsPacket *p, AvahiKey *k, int unicast_response);
void avahi_dns_packet_free(AvahiDnsPacket *p);
}

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
  char *host_name;

  if (size > AVAHI_DNS_PACKET_SIZE_MAX)
    return 0;

  avahi_set_log_function(log_function);

  if (!(p1 = avahi_dns_packet_new(size + AVAHI_DNS_PACKET_EXTRA_SIZE)))
    goto finish;

  memcpy(AVAHI_DNS_PACKET_DATA(p1), data, size);
  p1->size = size;

  if (avahi_dns_packet_check_valid(p1) < 0)
    goto finish;

  if (!(p2 = avahi_dns_packet_new(size + AVAHI_DNS_PACKET_EXTRA_SIZE)))
    goto finish;

  avahi_dns_packet_set_field(p2, AVAHI_DNS_FIELD_ID, avahi_dns_packet_get_field(p1, AVAHI_DNS_FIELD_ID));

  for (uint16_t n = avahi_dns_packet_get_field(p1, AVAHI_DNS_FIELD_QDCOUNT); n > 0; n--) {
    AvahiKey *key;
    int unicast_response = 0;
    uint8_t *res;

    if (!(key = avahi_dns_packet_consume_key(p1, &unicast_response)))
      goto finish;

    avahi_free(avahi_key_to_string(key));

    domain_ends_with_mdns_suffix(key->name);

    res = avahi_dns_packet_append_key(p2, key, unicast_response);
    avahi_key_unref(key);
    if (!res)
      goto finish;
    avahi_dns_packet_inc_field(p2, AVAHI_DNS_FIELD_QDCOUNT);
  }

  if (!copy_rrs(p1, p2, AVAHI_DNS_FIELD_ANCOUNT))
    goto finish;

  if (!copy_rrs(p1, p2, AVAHI_DNS_FIELD_NSCOUNT))
    goto finish;

  if (!copy_rrs(p1, p2, AVAHI_DNS_FIELD_ARCOUNT))
    goto finish;

  host_name = avahi_get_host_name_strdup();

finish:
  if (p2)
    avahi_dns_packet_free(p2);
  if (p1)
    avahi_dns_packet_free(p1);
  if (host_name)
    free(host_name);

  return 0;
}