 #include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/string-list.h"
#include "avahi-core/log.h"

void log_function(AvahiLogLevel level, const char *txt) {}

struct AvahiStringList * avahi_string_list_add_pair(struct AvahiStringList * l, char * key, char * value) {
  struct AvahiStringList *p;

  if (!l)
    l = avahi_string_list_new();

  p = l;
  while (p->next)
    p = p->next;

  p->next = avahi_string_list_new();
  p->next->key = avahi_strdup(key);
  p->next->value = avahi_strdup(value);

  return l;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiStringList *l = NULL;
  char *key = NULL, *value = NULL;
  FuzzedDataProvider stream(data, size);

  avahi_set_log_function(log_function);

  key = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024)).c_str();
  value = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024)).c_str();

  l = avahi_string_list_add_pair(l, key, value);

  avahi_string_list_free(l);

  return 0;
}