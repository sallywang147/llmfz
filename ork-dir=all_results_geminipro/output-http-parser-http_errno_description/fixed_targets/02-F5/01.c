#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <http_errno.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }
  const int err = *(const int *)data;
  const char *desc = http_errno_description(err);
  if (desc != NULL) {
    free((void *)desc);  // Fix: Cast `desc` to `(void *)` before passing it to `free()`
  }
  return 0;
}