#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "avahi-common/strlst.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the Avahi library
  avahi_init();

  // Call the function to fuzz
  char* hostname = avahi_get_host_name_strdup();

  // Free the memory allocated by avahi_get_host_name_strdup
  avahi_free(hostname);

  return 0;
}