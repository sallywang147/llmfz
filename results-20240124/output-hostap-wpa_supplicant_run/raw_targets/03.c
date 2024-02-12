 #include "includes.h"
#include "common.h"
#include "wpa_supplicant_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct wpa_global *global = wpa_supplicant_init(0);
  if (global == NULL) {
    return 0;
  }
  wpa_supplicant_run(global);
  wpa_supplicant_deinit(global);
  return 0;
}