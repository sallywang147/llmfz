#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/log.h"

void log_function(AvahiLogLevel level, const char *txt) {}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *ret_s = NULL;

  avahi_set_log_function(log_function);

  if (size > AVAHI_MAX_HOST_NAME_LENGTH)
    return 0;

  ret_s = avahi_get_host_name(ret_s, size);
  if (!ret_s)
    return 0;

  avahi_free(ret_s);

  return 0;
}