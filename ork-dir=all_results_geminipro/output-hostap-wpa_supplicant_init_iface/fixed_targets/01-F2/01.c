#include <fuzzer/FuzzedDataProvider.h>

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
  wpa_supplicant* wpa_s = wpa_supplicant_init();
  if (wpa_s == nullptr) {
    return 0;
  }

  wpa_interface iface;
  memset(&iface, 0, sizeof(iface));
  iface.ifname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 20)).c_str();
  iface.driver = stream.PickValueInArray(
      wpa_supplicant_drivers);

  int ret = wpa_supplicant_init_iface(wpa_s, &iface);
  wpa_supplicant_deinit(wpa_s);
  return ret;
}