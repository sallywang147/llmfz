#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

extern "C" {
#include "fuzzedDataProvider.h"
#include "libfuzzer/libfuzzer_macro.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  int err_code = stream.ConsumeIntegral<int>();
  const char *err_name = http_errno_name((enum http_errno)err_code);
  if (err_name != NULL) {
    free((char *)err_name);
  }
  return 0;
}