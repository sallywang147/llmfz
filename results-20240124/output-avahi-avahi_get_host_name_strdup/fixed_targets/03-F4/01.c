#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-common/timeval.h"
#include "avahi-core/domain.h"
#include "avahi-core/error.h"
#include "avahi-core/host-cache.h"
#include "avahi-core/log.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

void domain_ends_with_mdns_suffix(const char *domain) {
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_LOCAL);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV4);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV6);
}

AvahiHostCacheEntry *host_cache_lookup(AvahiHostCache *cache, const char *name, AvahiIfIndex interface) {
  return avahi_host_cache_lookup(cache, name, interface);
}

char *avahi_get_host_name_strdup() {
  char *hostname = avahi_get_host_name();
  if (!hostname)
    return NULL;

  char *dup = avahi_strdup(hostname);
  avahi_free(hostname);

  return dup;
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  avahi_set_log_function(log_function);
  avahi_get_host_name_strdup();
  return 0;
}