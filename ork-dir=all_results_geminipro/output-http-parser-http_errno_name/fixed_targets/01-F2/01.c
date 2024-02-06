#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "http_errno.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }
  int value = *(int *)data;
  const char *result = http_errno_name(value);
  if (result) {
    free((void *)result);
  }
  return 0;
}