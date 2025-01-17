 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/log.h"

void log_function(AvahiLogLevel level, const char *txt) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  avahi_set_log_function(log_function);
  char *host_name = avahi_get_host_name_strdup();
  if (host_name != nullptr) {
    free(host_name);
  }
  return 0;
}