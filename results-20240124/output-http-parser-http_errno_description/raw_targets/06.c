 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  int err = stream.ConsumeIntegralInRange(0, 100000);

  char * description = http_errno_description(err);
  if (description != NULL)
    free(description);

  return 0;
}