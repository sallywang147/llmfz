 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  int errno = (int)data[0];
  char * description = http_errno_description(errno);
  free(description);

  return 0;
}