#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

extern "C" {
#include "http_parser.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  char * err_name = http_errno_name((http_errno)data[0] % HTTP_PARSER_ERRNO_MAX);
  return 0;
}