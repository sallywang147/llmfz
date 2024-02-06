#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  uint32_t key = *(uint32_t *)data;
  cdtext_get_key(key, 0);
  return 0;
}