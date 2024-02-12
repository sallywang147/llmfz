#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/log.h"
#include "avahi-core/network.h"

extern "C" {
#include "avahi-core/error.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  avahi_set_log_function(log_function);

  FuzzedDataProvider provider(data, size);
  const size_t requested_size = provider.ConsumeIntegralInRange<size_t>(
      0, 1000);
  char *host_name = static_cast<char*>(avahi_malloc(requested_size));
  if (host_name == nullptr) {
    return 0;
  }
  avahi_get_host_name(host_name, requested_size);
  avahi_free(host_name);

  return 0;
}