#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/string-list.h"
#include "avahi-core/log.h"

extern "C" {
void log_function(AvahiLogLevel level, const char *txt) {}
}

void domain_ends_with_mdns_suffix(const char *domain) {
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_LOCAL);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV4);
  avahi_domain_ends_with(domain, AVAHI_MDNS_SUFFIX_ADDR_IPV6);
}

struct AvahiStringList *avahi_string_list_add_pair(struct AvahiStringList *l, char *key, char *value) {
  struct AvahiStringList *p;
  size_t key_len, val_len;

  if (!l)
    return NULL;

  key_len = strlen(key) + 1;
  val_len = strlen(value) + 1;

  p = avahi_malloc(sizeof(struct AvahiStringList) + key_len + val_len);
  if (!p)
    return NULL;

  p->next = l;
  p->key = (char *)p + sizeof(struct AvahiStringList);
  p->value = p->key + key_len;

  memcpy(p->key, key, key_len);
  memcpy(p->value, value, val_len);

  return p;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct AvahiStringList *l = NULL;
  size_t i;
  char key[128];
  char val[128];

  avahi_set_log_function(log_function);

  for (i = 0; i < size; i++) {
    if (data[i] == '\n') {
      l = avahi_string_list_add_pair(l, key, val);
      key[0] = '\0';
      val[0] = '\0';
    } else if (data[i] == '=') {
      key[strlen(key)] = '\0';
    } else {
      key[strlen(key)] = data[i];
      val[strlen(val)] = data[i];
    }
  }

  avahi_string_list_free(l);

  return 0;
}