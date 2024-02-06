#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  int err_code = *(int *)data;
  char *err_name = llhttp_errno_name(err_code);
  if (err_name == NULL) {
    return 0;
  }
  return 0;
}