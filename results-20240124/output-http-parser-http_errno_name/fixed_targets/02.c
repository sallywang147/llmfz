 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  int err = *data;
  char * name = http_errno_name(err);
  if (name == NULL)
    return 0;
  return 0;
}