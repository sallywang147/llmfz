 #include <fuzzer/FuzzedDataProvider.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/string-list.h"
#include "avahi-core/log.h"

void log_function(AvahiLogLevel level, const char *txt) {}

void avahi_string_list_free(AvahiStringList *l) {
  avahi_string_list_free_deep(l);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiStringList *l = NULL;
  FuzzedDataProvider stream(data, size);

  avahi_set_log_function(log_function);

  l = avahi_string_list_add_pair(l, stream.ConsumeBytesAsString().c_str(), stream.ConsumeBytesAsString().c_str());
  if (l)
    avahi_string_list_free(l);

  return 0;
}