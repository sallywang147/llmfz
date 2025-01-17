#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct wpa_supplicant wpa_s;
  struct wpa_interface iface;

  // Initialize the wpa_supplicant structure
  os_memset(&wpa_s, 0, sizeof(wpa_s));
  wpa_s.global = (struct wpa_global*) os_zalloc(sizeof(struct wpa_global));
  if (wpa_s.global == NULL) {
    return 0;
  }

  // Initialize the wpa_interface structure
  os_memset(&iface, 0, sizeof(iface));

  // Consume data from the fuzzer input
  iface.driver = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.ifname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.confname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.ctrl_interface = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  iface.driver_param = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str();

  // Call the function to fuzz
  wpa_supplicant_init_iface(&wpa_s, &iface);

  // Cleanup
  os_free(wpa_s.global);

  return 0;
}