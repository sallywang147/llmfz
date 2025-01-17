 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  int status = stream.ConsumeIntegral<int>();
  char *s = http_status_str(status);
  free(s);

  return 0;
}