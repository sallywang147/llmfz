#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  int status = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
  char *status_name = llhttp_status_name(status);
  free(status_name);
  return 0;
}