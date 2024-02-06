#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libcue.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int key_count = cdtext_get_key_count();
  for (int i = 0; i < key_count; i++) {
    char *key = cdtext_get_key(i, 0);
    // Do something with the key.
    free(key);
  }
  return 0;
}