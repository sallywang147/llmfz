#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct wpa_supplicant wpa_s;
  memset(&wpa_s, 0, sizeof(wpa_s));

  struct wpa_interface iface;
  memset(&iface, 0, sizeof(iface));

  iface.ifname = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  iface.driver = stream.PickValueInArray(wpa_drivers);
  iface.conf = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1000)).c_str();

  wpa_supplicant_init_iface(&wpa_s, &iface);

  return 0;
}