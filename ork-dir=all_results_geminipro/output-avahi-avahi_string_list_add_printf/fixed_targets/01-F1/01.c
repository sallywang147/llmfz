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

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiStringList *l = NULL;
  char *format = NULL;

  if (size > AVAHI_STRING_LIST_MAX_LEN)
    return 0;

  avahi_set_log_function(log_function);

  if (!(format = avahi_malloc(size + 1)))
    goto finish;

  memcpy(format, data, size);
  format[size] = '\0';

  l = avahi_string_list_add_printf(l, format);

finish:
  if (l)
    avahi_string_list_free(l);
  if (format)
    avahi_free(format);

  return 0;
}