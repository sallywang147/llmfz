#include <stddef.h>
#include <stdint.h>

#include "fuzzer.h"

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
}

static struct wpa_supplicant *wpa_s;
static struct wpa_interface *iface;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  wpa_supplicant_init_iface(wpa_s, iface);
  // ...
  return 0;
}