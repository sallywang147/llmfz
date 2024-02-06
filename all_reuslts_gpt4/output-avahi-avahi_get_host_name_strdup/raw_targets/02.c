#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "avahi-common/strlst.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char *host_name = avahi_get_host_name_strdup();
  if (host_name) {
    free(host_name);
  }
  return 0;
}