#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wpa_supplicant wpa_s;
  struct wpa_interface iface;

  const std::string ifname = stream.ConsumeRemainingBytesAsString();
  iface.ifname = const_cast<char*>(ifname.c_str());

  wpa_supplicant_init_iface(&wpa_s, &iface);

  return 0;
}