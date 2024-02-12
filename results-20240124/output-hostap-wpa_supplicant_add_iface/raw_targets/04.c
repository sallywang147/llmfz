 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "wpa_supplicant/wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> global_data = provider.ConsumeBytes<uint8_t>(size);
  struct wpa_global* global = reinterpret_cast<struct wpa_global*>(global_data.data());

  std::vector<uint8_t> iface_data = provider.ConsumeBytes<uint8_t>(size);
  struct wpa_interface* iface = reinterpret_cast<struct wpa_interface*>(iface_data.data());

  std::vector<uint8_t> parent_data = provider.ConsumeBytes<uint8_t>(size);
  struct wpa_supplicant* parent = reinterpret_cast<struct wpa_supplicant*>(parent_data.data());

  wpa_supplicant_add_iface(global, iface, parent);

  return 0;
}