#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "dns/view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the dns view
  dns_view_t *view = NULL;
  dns_result_t result = dns_view_create(isc_mem_create(), "view", &view);
  if (result != ISC_R_SUCCESS) {
    return 0;
  }

  // Consume data from the fuzzer input
  bool value = stream.ConsumeBool();

  // Call the function to be fuzzed
  dns_view_freezezones(view, value);

  // Clean up
  dns_view_detach(&view);

  return 0;
}