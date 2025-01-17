#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "dns/view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  dns_view_t *view = nullptr;
  if (dns_view_create(0, "default", &view) != ISC_R_SUCCESS) {
    return 0;
  }

  bool value = stream.ConsumeBool();
  dns_view_freezezones(view, value);

  dns_view_detach(&view);

  return 0;
}