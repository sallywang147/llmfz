 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  int errnum = data[0];
  char *desc = http_errno_description(errnum);
  if (desc != NULL)
    free(desc);

  return 0;
}