#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer.h"

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
}

static struct wpa_global *global;

static int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (global == NULL) {
    global = wpa_supplicant_init();
    if (global == NULL) {
      return 0;
    }
  }

  wpa_supplicant_run(global);

  return 0;
}

int main(int argc, char **argv) {
  LLVMFuzzerInitialize(argc, argv);
  LLVMFuzzerTestOneInput(NULL, 0);
  return 0;
}