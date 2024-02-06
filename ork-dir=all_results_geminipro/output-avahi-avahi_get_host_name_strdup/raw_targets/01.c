#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/timeval.h"
#include "avahi-core/log.h"

void log_function(AvahiLogLevel level, const char *txt) {}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *hostname;

  avahi_set_log_function(log_function);

  hostname = avahi_get_host_name_strdup();
  if (!hostname)
    return 0;

  avahi_free(hostname);
  return 0;
}