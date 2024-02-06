#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 8) {
    return 0;
  }
  uint8_t *p = (uint8_t *)data;
  log_append_common((struct Log *)p, p[4], p[5], (char *)p + 6, (char *)p + 8, p[12], (char *)p + 13);
  return 0;
}