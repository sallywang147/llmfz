#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct wpa_global *global = wpa_supplicant_init(&eloop, NULL);
  if (global == NULL) {
    return 0;
  }

  struct wpa_supplicant *wpa_s;
  wpa_s = wpa_supplicant_add_iface(global, NULL);
  if (wpa_s == NULL) {
    wpa_supplicant_deinit(global);
    return 0;
  }

  // Generate random data for wpa_s->conf->ssid
  struct wpa_ssid *ssid = (struct wpa_ssid *)os_zalloc(sizeof(struct wpa_ssid));
  if (ssid == NULL) {
    wpa_supplicant_remove_iface(global, wpa_s);
    wpa_supplicant_deinit(global);
    return 0;
  }
  ssid->ssid_len = stream.ConsumeIntegralInRange<size_t>(0, sizeof(ssid->ssid));
  std::vector<uint8_t> ssid_data = stream.ConsumeBytes<uint8_t>(ssid->ssid_len);
  os_memcpy(ssid->ssid, ssid_data.data(), ssid->ssid_len);
  wpa_s->conf->ssid = ssid;

  // Run the function to fuzz
  wpa_supplicant_run(global);

  // Clean up
  os_free(ssid);
  wpa_supplicant_remove_iface(global, wpa_s);
  wpa_supplicant_deinit(global);

  return 0;
}