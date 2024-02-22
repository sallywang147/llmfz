 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  if (size > 0) {
    int status = data[0];
    char *status_str = http_status_str(status);
    free(status_str);
  }

  return 0;
}