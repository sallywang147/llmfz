#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dropbear.h"

extern "C" {
#include "dropbear_fuzz.h"
}

int LLVMFuzzerTestOneInput(const unsigned char* data, size_t size) {
  dropbear_fuzz_test(data, size);

  /* Call the target function here */
  struct dropbear_DSS_Key *key = gen_rsa_priv_key(2048);
  dropbear_free(key);

  return 0;
}