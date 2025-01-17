#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "signkey.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  int keytype = data[0];
  int bits = data[1];
  char filename[256];
  snprintf(filename, sizeof(filename), "/tmp/signkey_fuzz_%d_%d", keytype, bits);
  int skip_exist = data[2];

  signkey_generate(keytype, bits, filename, skip_exist);

  return 0;
}