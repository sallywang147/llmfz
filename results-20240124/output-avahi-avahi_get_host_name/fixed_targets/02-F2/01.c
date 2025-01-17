#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/log.h"
#include "avahi-core/utils.h"

extern "C" {
#include "avahi-core/utils.h"
}

void log_function(AvahiLogLevel level, const char *txt) {}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  avahi_set_log_function(log_function);

  FuzzedDataProvider provider(data, size);
  const size_t hostname_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  char hostname[hostname_size + 1];
  avahi_get_host_name(hostname, hostname_size + 1);
  return 0;
}