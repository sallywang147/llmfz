#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>
#include <cstring>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-core/util.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  avahi_set_log_function(log_function);

  FuzzedDataProvider provider(data, size);
  const char* name = provider.ConsumeRemainingBytesAsString().c_str();
  char *hostname = avahi_get_host_name_strdup(name);
  avahi_free(hostname);
  return 0;
}