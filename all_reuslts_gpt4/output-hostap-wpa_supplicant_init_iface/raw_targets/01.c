#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct wpa_supplicant wpa_s;
  struct wpa_interface iface;

  // Initialize wpa_supplicant and wpa_interface with data from the fuzzer
  wpa_s.ifname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  wpa_s.confname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  wpa_s.confanothername = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();

  iface.driver = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.ifname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.ctrl_interface = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.ctrl_interface_group = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.driver_param = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.config_file = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.bridge_ifname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();

  // Call the function to fuzz
  int ret = wpa_supplicant_init_iface(&wpa_s, &iface);

  return 0;
}