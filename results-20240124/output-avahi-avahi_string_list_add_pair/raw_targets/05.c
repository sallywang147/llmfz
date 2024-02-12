 #include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/string.h"
#include "avahi-common/strlst.h"

void log_function(AvahiLogLevel level, const char *txt) {}

AvahiStringList *avahi_string_list_add_pair(AvahiStringList *l, char *key, char *value) {
  AvahiStringList *new_entry;
  AvahiStringList *old_entry;

  if (!l)
    return NULL;

  new_entry = avahi_malloc(sizeof(AvahiStringList));
  if (!new_entry)
    return NULL;

  new_entry->key = avahi_strdup(key);
  if (!new_entry->key) {
    avahi_free(new_entry);
    return NULL;
  }

  new_entry->value = avahi_strdup(value);
  if (!new_entry->value) {
    avahi_free(new_entry->key);
    avahi_free(new_entry);
    return NULL;
  }

  new_entry->next = NULL;

  old_entry = l;
  while (old_entry->next)
    old_entry = old_entry->next;

  old_entry->next = new_entry;

  return l;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiStringList *list = NULL;
  FuzzedDataProvider stream(data, size);

  avahi_set_log_function(log_function);

  while (stream.remaining_bytes() > 0) {
    size_t key_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
    size_t value_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
    char *key = stream.ConsumeBytes<char>(key_size).data();
    char *value = stream.ConsumeBytes<char>(value_size).data();
    list = avahi_string_list_add_pair(list, key, value);
  }

  avahi_string_list_free(list);
  return 0;
}