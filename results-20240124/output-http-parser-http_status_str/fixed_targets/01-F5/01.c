#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  FuzzedDataProvider stream(data, size);

  int status_code = stream.ConsumeIntegralInRange<int>(100, 599);
  const char *status_str = http_status_str((enum http_status)status_code);
  free((void*)status_str);

  return 0;
}