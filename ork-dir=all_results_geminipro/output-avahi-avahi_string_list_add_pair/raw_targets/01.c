#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/stringlist.h"

void log_function(AvahiLogLevel level, const char *txt) {}

struct AvahiStringList * avahi_string_list_add_pair(struct AvahiStringList * l, char * key, char * value) {
  struct AvahiStringList *p;

  if (!l) {
    l = avahi_string_list_new();
    if (!l)
      return NULL;
  }

  p = avahi_string_list_add(l, key, value);
  if (!p) {
    avahi_string_list_free(l);
    return NULL;
  }

  return p;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct AvahiStringList *l = NULL;
  char *key = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *value = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();

  avahi_set_log_function(log_function);

  l = avahi_string_list_add_pair(l, key, value);
  avahi_string_list_free(l);

  return 0;
}