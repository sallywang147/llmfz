#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "wpa_supplicant/wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wpa_global global;
  wpa_supplicant_init(&global);

  int ret = wpa_supplicant_run(&global);

  wpa_supplicant_deinit(&global);

  return ret;
}