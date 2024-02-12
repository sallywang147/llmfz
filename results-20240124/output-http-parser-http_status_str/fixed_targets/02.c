 #include <stdint.h>
#include <stdlib.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  if (size == 0)
    return 0;

  int status_code = data[0];
  char *status_str = http_status_str(status_code);
  free(status_str);

  return 0;
}