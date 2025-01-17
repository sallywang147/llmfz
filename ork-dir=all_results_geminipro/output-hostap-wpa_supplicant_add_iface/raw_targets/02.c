#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "wpa_supplicant/wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string global_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange<size_t>(0, 16));
  struct wpa_global *global = wpa_supplicant_init(global_name.c_str());
  if (global == nullptr) {
    return 0;
  }

  const std::string interface_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange<size_t>(0, 16));
  struct wpa_interface *interface =
      wpa_supplicant_get_iface(global, interface_name.c_str());
  if (interface == nullptr) {
    wpa_supplicant_deinit(global);
    return 0;
  }

  const std::string parent_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange<size_t>(0, 16));
  struct wpa_supplicant *parent =
      wpa_supplicant_get_iface(global, parent_name.c_str());
  if (parent == nullptr) {
    wpa_supplicant_deinit(global);
    return 0;
  }

  struct wpa_supplicant *supplicant =
      wpa_supplicant_add_iface(global, interface, parent);
  if (supplicant != nullptr) {
    wpa_supplicant_remove_iface(global, supplicant, 0);
  }
  wpa_supplicant_deinit(global);
  return 0;
}