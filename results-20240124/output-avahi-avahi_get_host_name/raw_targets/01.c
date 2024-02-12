 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-common/timeval.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char* hostname = avahi_get_host_name(nullptr, 0);
  if (hostname == nullptr) {
    return 0;
  }
  free(hostname);
  return 0;
}