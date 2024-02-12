 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  if (size < 1) return 0;
  char * status = http_status_str(data[0]);
  free(status);
  return 0;
}