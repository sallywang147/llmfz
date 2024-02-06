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
  char *desc = http_errno_description(err);
  if (desc != NULL) {
    free(desc);
  }
  return 0;
}