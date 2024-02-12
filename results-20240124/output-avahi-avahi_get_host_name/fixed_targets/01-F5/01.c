#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-common/timeval.h"

extern "C" {
#include "avahi-common/simple-watch.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/thread-watch.h"
#include "avahi-common/timeval.h"
#include "dnssd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char* hostname = avahi_get_host_name();
  if (hostname == nullptr) {
    return 0;
  }
  free(hostname);
  return 0;
}