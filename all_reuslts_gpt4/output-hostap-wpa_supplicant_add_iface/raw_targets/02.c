#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    wpa_debug_open_file("wpa_supplicant.log");
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  struct wpa_global *global = wpa_supplicant_init();
  if (global == nullptr) {
    return 0;
  }

  struct wpa_interface iface;
  iface.driver = stream.ConsumeRandomLengthString().c_str();
  iface.ifname = stream.ConsumeRandomLengthString().c_str();
  iface.confname = stream.ConsumeRandomLengthString().c_str();
  iface.ctrl_interface = stream.ConsumeRandomLengthString().c_str();
  iface.driver_param = stream.ConsumeRandomLengthString().c_str();
  iface.bridge_ifname = stream.ConsumeRandomLengthString().c_str();

  struct wpa_supplicant *parent = nullptr;
  if(stream.ConsumeBool()) {
    parent = wpa_supplicant_add_iface(global, &iface, nullptr);
  }

  struct wpa_supplicant *wpa_s = wpa_supplicant_add_iface(global, &iface, parent);

  if(wpa_s != nullptr) {
    wpa_supplicant_remove_iface(global, wpa_s);
  }

  if(parent != nullptr) {
    wpa_supplicant_remove_iface(global, parent);
  }

  wpa_supplicant_deinit(global);

  return 0;
}