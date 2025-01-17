#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct wpa_global global;
  memset(&global, 0, sizeof(global));

  struct wpa_params params;
  memset(&params, 0, sizeof(params));

  // Initialize wpa_global structure
  global.params = &params;

  // Extract data for wpa_global structure
  global.params->wpa_debug_level = stream.ConsumeIntegral<int>();
  global.params->wpa_debug_show_keys = stream.ConsumeBool();
  global.params->wpa_debug_timestamp = stream.ConsumeBool();

  // Call the function to fuzz
  wpa_supplicant_run(&global);

  return 0;
}