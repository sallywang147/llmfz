#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wpa_supplicant* parent = nullptr;
  struct wpa_interface* iface = nullptr;
  struct wpa_global* global = nullptr;
  wpa_supplicant_add_iface(global, iface, parent);
  return 0;
}