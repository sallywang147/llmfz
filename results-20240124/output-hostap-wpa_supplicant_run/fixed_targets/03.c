#include "includes.h"
#include "common.h"
#include "wpa_supplicant_i.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "wpa_fuzzer_i.h"

#ifdef __cplusplus
}
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct wpa_global *global = wpa_supplicant_init(0);
  if (global == NULL) {
    return 0;
  }
  wpa_fuzzer_set_debug_level(global, 1);
  wpa_supplicant_run(global);
  wpa_supplicant_deinit(global);
  return 0;
}