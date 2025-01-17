#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "dns/zone.h"
#include "dns/view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  dns_zt_t *zt = nullptr;
  dns_view_t *view = nullptr;

  // Initialize the libraries
  dns_zt_create(NULL, &zt);
  dns_view_create(NULL, &view);

  // Get the boolean value from the stream
  bool freeze = stream.ConsumeBool();

  // Call the target function
  dns_zt_freezezones(zt, view, freeze);

  // Clean up
  dns_zt_detach(&zt);
  dns_view_detach(&view);

  return 0;
}