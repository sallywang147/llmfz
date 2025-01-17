#include "http_parser.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int statusCode = stream.ConsumeIntegral<int>();
  char *statusStr = http_status_str(statusCode);
  return 0;
}