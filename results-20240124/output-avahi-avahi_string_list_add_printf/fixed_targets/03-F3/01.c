#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"

extern "C" {
#include "avahi-client/client.h"
#include "avahi-client/lookup.h"
#include "avahi-client/publish.h"
#include "avahi-client/query.h"  // Fix: Include the missing header
#include "avahi-core/string-list.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

void domain_ends_with_mdns_suffix(const char *domain) {
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_LOCAL);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV4);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV6);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiStringList *l = avahi_string_list_new();
  if (!l)
    return 0;

  avahi_set_log_function(log_function);

  char *format = (char *)avahi_malloc(size + 1);
  if (!format)
    goto finish;

  memcpy(format, data, size);
  format[size] = '\0';

  avahi_string_list_add_printf(l, format);

finish:
  if (l)
    avahi_string_list_free(l);
  if (format)
    avahi_free(format);

  return 0;
}