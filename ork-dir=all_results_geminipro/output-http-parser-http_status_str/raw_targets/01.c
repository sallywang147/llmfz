#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int status_code = *(int *)data;
  char *status_str = http_status_str(status_code);
  free(status_str);
  return 0;
}