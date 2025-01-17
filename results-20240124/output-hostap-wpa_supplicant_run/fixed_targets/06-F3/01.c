#include <fuzzer/FuzzedDataProvider.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
#include <algorithm>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct wpa_global *global = wpa_supplicant_init();
  if (global == NULL) {
    fprintf(stderr, "wpa_supplicant_init failed: %s\n", strerror(errno));
    exit(1);
  }

  FuzzedDataProvider stream(data, size);
  int ret = wpa_supplicant_run(global);
  assert(ret == 0);

  wpa_supplicant_deinit(global);
  return 0;
}