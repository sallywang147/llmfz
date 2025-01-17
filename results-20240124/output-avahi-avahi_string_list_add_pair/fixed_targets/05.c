#include <stddef.h>
#include "avahi-common/log.h"

extern "C" {
#include "avahi-common/string-list.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiStringList *l = avahi_string_list_new();
  avahi_string_list_add_pair(l, "key", "value");
  avahi_string_list_free(l);
  return 0;
}