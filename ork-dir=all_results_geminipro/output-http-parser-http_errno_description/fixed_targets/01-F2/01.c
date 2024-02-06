#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "http_parser.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  int http_errno = data[0];
  const char *description = http_errno_description(http_errno);
  free((void *)description);
  return 0;
}