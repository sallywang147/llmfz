 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "hostapd.h"
#include "hostapd_config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct hostapd_iface iface;
  iface.conf = os_zalloc(sizeof(*iface.conf));
  if (iface.conf == nullptr) {
    return 0;
  }

  iface.conf->ssid.ssid = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 32));
  iface.conf->ssid.ssid_len = strlen(iface.conf->ssid.ssid);
  iface.conf->ssid.wpa_passphrase = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 63));
  iface.conf->ssid.wpa_passphrase_len = strlen(iface.conf->ssid.wpa_passphrase);

  hostapd_reload_config(&iface);

  os_free(iface.conf);
  return 0;
}