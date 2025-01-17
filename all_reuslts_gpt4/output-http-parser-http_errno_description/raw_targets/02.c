#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int errno_value = stream.ConsumeIntegral<int>();
  char* error_description = http_errno_description(errno_value);
  return 0;
}