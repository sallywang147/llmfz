#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
extern "C" {
#include "avahi-core/string-list.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

void domain_ends_with_mdns_suffix(const char *domain) {
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_LOCAL);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV4);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV6);
}

struct AvahiStringList *avahi_string_list_add_printf(struct AvahiStringList *l, char *format) {
  char *s;
  struct AvahiStringList *ret;

  if (!l)
    return NULL;

  if (vasprintf(&s, format, l->entries) < 0)
    return NULL;

  domain_ends_with_mdns_suffix(s);

  ret = avahi_string_list_add_string(l, s);
  free(s);

  return ret;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct AvahiStringList *list = avahi_string_list_new();
  FuzzedDataProvider stream(data, size);
  char *format = stream.ConsumeRemainingBytesAsString().c_str();
  avahi_string_list_add_printf(list, format);
  avahi_string_list_free(list);
  return 0;
}