 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "wpa_supplicant/wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct wpa_global *global = wpa_supplicant_init();
  if (global == nullptr) {
    return 0;
  }
  struct wpa_interface *iface =
      wpa_supplicant_get_iface(global, provider.ConsumeRandomLengthString());
  if (iface == nullptr) {
    wpa_supplicant_deinit(global);
    return 0;
  }
  struct wpa_supplicant *parent =
      wpa_supplicant_get_iface(global, provider.ConsumeRandomLengthString());
  wpa_supplicant_add_iface(global, iface, parent);
  wpa_supplicant_deinit(global);
  return 0;
}