#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "http_parser.h"

extern "C" {
#include "http_parser.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int status_code = *(int *)data;
  const char *status_str = http_status_str(status_code);
  if (status_str != NULL) {
    free((void *)status_str);  // Fix: Cast status_str to void * before calling free
  }
  return 0;
}