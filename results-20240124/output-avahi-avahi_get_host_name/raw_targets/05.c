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

  FuzzedDataProvider stream(data, size);
  const size_t hostname_size = stream.ConsumeIntegralInRange<size_t>(
      1, 255);
  char hostname[hostname_size];
  avahi_get_host_name(hostname, hostname_size);

  return 0;
}