#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-core/log.h"

extern "C" {
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/timeval.h"
#include "avahi-core/address-resolver.h"
#include "avahi-core/config.h"
#include "avahi-core/core.h"
#include "avahi-core/domain.h"
#include "avahi-core/error.h"
#include "avahi-core/get-host-name.h"
#include "avahi-core/lookup.h"
#include "avahi-core/publish.h"
#include "avahi-core/query.h"
#include "avahi-core/resolver.h"
#include "avahi-core/server.h"
#include "avahi-core/service-type-database.h"
#include "avahi-core/string.h"
#include "avahi-core/txt-record.h"
}

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