 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  char *status = http_status_str(data[0]);
  if (status)
    free(status);

  return 0;
}