#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }
  int value = *(int *)data;
  char *result = http_errno_name(value);
  free(result);
  return 0;
}