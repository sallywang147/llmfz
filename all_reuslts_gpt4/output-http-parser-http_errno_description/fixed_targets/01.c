#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int err_no = stream.ConsumeIntegral<int>();
  char *description = http_errno_description(err_no);
  return 0;
}