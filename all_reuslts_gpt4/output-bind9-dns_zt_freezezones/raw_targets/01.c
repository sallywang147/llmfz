#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "dns/zt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize dns_zt and dns_view objects
  struct dns_zt *zt = dns_zt_create();
  struct dns_view *view = dns_view_create();

  // Extract boolean value
  bool freeze = stream.ConsumeBool();

  // Call the target function
  dns_zt_freezezones(zt, view, freeze);

  // Cleanup
  dns_zt_destroy(zt);
  dns_view_destroy(view);

  return 0;
}