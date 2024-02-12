 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "wpa_supplicant/wpa_supplicant.h"
#include "wpa_supplicant/driver.h"
#include "wpa_supplicant/wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wpa_supplicant wpa_s;
  struct wpa_interface iface;
  memset(&wpa_s, 0, sizeof(wpa_s));
  memset(&iface, 0, sizeof(iface));
  wpa_s.conf = &iface.conf;
  iface.driver = &wpa_drivers[0];
  iface.driver_ctx = NULL;
  iface.driver_radio_idx = 0;
  iface.conf->ap_scan = 2;
  iface.conf->scan_interval = 10;
  iface.conf->fast_reauth = 1;
  iface.conf->wpa_disable_roaming = 0;
  iface.conf->wpa_deny_ptk0_rekey = 0;
  iface.conf->wpa_drop_unenc = 0;
  iface.conf->wpa_strict_rekey = 0;
  iface.conf->wpa_pairwise = WPA_CIPHER_CCMP;
  iface.conf->wpa_group = WPA_CIPHER_CCMP;
  iface.conf->wpa_key_mgmt = WPA_KEY_MGMT_PSK;
  iface.conf->wpa_proto = WPA_PROTO_RSN;
  iface.conf->wpa_pairwise_cipher = WPA_CIPHER_CCMP;
  iface.conf->wpa_group_cipher = WPA_CIPHER_CCMP;
  iface.conf->wpa_passphrase = "password";
  iface.conf->wpa_psk = (uint8_t*)"password";
  iface.conf->wpa_psk_len = 8;
  iface.conf->ssid = (uint8_t*)"ssid";
  iface.conf->ssid_len = 4;
  iface.conf->bssid = (uint8_t*)"00:00:00:00:00:00";
  iface.conf->bssid_set = 1;
  iface.conf->wpa = 1;
  wpa_supplicant_init_iface(&wpa_s, &iface);
  return 0;
}