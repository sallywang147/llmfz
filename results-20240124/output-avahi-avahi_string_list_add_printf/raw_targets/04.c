 #include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/string-list.h"

void log_function(AvahiLogLevel level, const char *txt) {}

struct AvahiStringList * avahi_string_list_add_printf(struct AvahiStringList * l, char * format) {
  return avahi_string_list_add_printf_vlist(l, format, NULL);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  avahi_set_log_function(log_function);

  char *str = (char *)avahi_malloc(size + 1);
  if (!str) return 0;

  memcpy(str, data, size);
  str[size] = '\0';

  struct AvahiStringList *l = avahi_string_list_new();
  if (!l) {
    avahi_free(str);
    return 0;
  }

  avahi_string_list_add_printf(l, str);

  avahi_free(str);
  avahi_string_list_free(l);

  return 0;
}