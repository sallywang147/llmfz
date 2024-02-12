#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "fuzz.h"

extern "C" {
#include "dropbear.h"
}

struct dropbear_DSS_Key * gen_rsa_priv_key(int size) {
  struct dropbear_DSS_Key *key = NULL;
  dropbear_dss_new_priv_key(&key, size);
  return key;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  struct dropbear_DSS_Key *key = gen_rsa_priv_key(data[0]);
  dropbear_dss_free(key);

  return 0;
}