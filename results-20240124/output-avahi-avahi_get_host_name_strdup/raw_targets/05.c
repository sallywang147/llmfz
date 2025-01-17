 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/log.h"

void log_function(AvahiLogLevel level, const char *txt) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  avahi_set_log_function(log_function);
  char *hostname = avahi_get_host_name_strdup();
  if (hostname == nullptr) {
    return 0;
  }
  avahi_free(hostname);
  return 0;
}