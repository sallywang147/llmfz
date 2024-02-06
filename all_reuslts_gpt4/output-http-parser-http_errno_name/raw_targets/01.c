#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int arg = stream.ConsumeIntegral<int>();
  http_errno_name(arg);
  return 0;
}