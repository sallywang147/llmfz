#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/error.h"
#include "avahi-core/log.h"
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
  int result = avahi_get_host_name(host_name, requested_size);
  if (result < 0) {
    avahi_free(host_name);
    return 0;
  }
  avahi_free(host_name);

  return 0;
}