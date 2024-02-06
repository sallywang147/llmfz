#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "http_parser.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) return 0;
  int err = data[0];
  const char *err_str = http_errno_name(err);
  if (err_str) {
    free((void *)err_str);
  }
  return 0;
}