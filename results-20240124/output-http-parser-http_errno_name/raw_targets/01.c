 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  int err_code = stream.ConsumeIntegral<int>();
  char * err_name = http_errno_name(err_code);
  if (err_name != NULL) {
    free(err_name);
  }
  return 0;
}