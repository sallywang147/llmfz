#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string interface_name = stream.ConsumeRemainingBytesAsString();
  struct wpa_supplicant *parent = nullptr;
  struct wpa_global *global = nullptr;
  struct wpa_interface *iface = wpa_supplicant_get_iface(global, interface_name.c_str());
  if (iface == nullptr) {
    return 0;
  }
  struct wpa_supplicant *supplicant =
      wpa_supplicant_add_iface(global, iface, parent);
  if (supplicant == nullptr) {
    return 0;
  }
  wpa_supplicant_remove_iface(global, supplicant, 0);
  wpa_supplicant_deinit(supplicant);
  return 0;
}