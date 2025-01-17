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
    wpa_supplicant_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize the global structure
  struct wpa_global global;
  global.params = provider.ConsumeIntegral<wpa_params>();
  global.ifaces = provider.ConsumeIntegral<wpa_supplicant*>();
  global.p2p = provider.ConsumeBool();
  global.p2p_init_wpa_s = provider.ConsumeIntegral<wpa_supplicant*>();
  global.p2p_group_formation = provider.ConsumeIntegral<wpa_supplicant*>();
  global.p2p_srv_bonjour = provider.ConsumeIntegral<struct wpabuf*>();
  global.p2p_srv_upnp = provider.ConsumeIntegral<struct wpabuf*>();
  global.p2p_disabled = provider.ConsumeBool();
  global.p2p_per_sta_psk = provider.ConsumeBool();
  global.p2p_fail_on_wps_complete = provider.ConsumeBool();
  global.p2p_radio = provider.ConsumeIntegral<struct wpa_radio*>();
  global.p2p_go_wait_client.sec = provider.ConsumeIntegral<int>();
  global.p2p_go_wait_client.usec = provider.ConsumeIntegral<int>();

  // Initialize the interface structure
  struct wpa_interface iface;
  iface.driver = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.ifname = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.ctrl_interface = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.driver_param = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.confname = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.confanother = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.conf_preprocess = provider.ConsumeBool();
  iface.split_conf = provider.ConsumeBool();

  // Initialize the parent structure
  struct wpa_supplicant parent;
  parent.global = &global;
  parent.ifname = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  parent.conf = provider.ConsumeIntegral<struct wpa_config*>();
  parent.confname = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();

  // Call the function
  wpa_supplicant_add_iface(&global, &iface, &parent);

  return 0;
}