#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  int err = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
  char *err_name = llhttp_errno_name(err);
  return 0;
}