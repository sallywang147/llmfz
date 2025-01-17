#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/string-list.h"

extern "C" {
#include "avahi-core/log.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

void avahi_string_list_ends_with_mdns_suffix(const char *str) {
  avahi_string_list_ends_with(str, AVAHI_MDNS_SUFFIX_LOCAL);
  avahi_string_list_ends_with(str, AVAHI_MDNS_SUFFIX_ADDR_IPV4);
  avahi_string_list_ends_with(str, AVAHI_MDNS_SUFFIX_ADDR_IPV6);
}

struct AvahiStringList * avahi_string_list_add_pair(struct AvahiStringList * l, char * key, char * value) {
  avahi_string_list_ends_with_mdns_suffix(key);
  avahi_string_list_ends_with_mdns_suffix(value);
  return avahi_string_list_add_pair(l, key, value);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  avahi_set_log_function(log_function);

  struct AvahiStringList *l = avahi_string_list_new();
  if (!l)
    return 0;

  FuzzedDataProvider stream(data, size);

  while (stream.remaining_bytes() > 0) {
    size_t key_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    size_t value_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    char *key = stream.ConsumeBytes<char>(key_size);
    char *value = stream.ConsumeBytes<char>(value_size);
    l = avahi_string_list_add_pair(l, key, value);
  }

  avahi_string_list_free(l);
  return 0;
}