#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    wpa_supplicant_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  struct wpa_global global;
  wpa_supplicant_run(&global);

  return 0;
}