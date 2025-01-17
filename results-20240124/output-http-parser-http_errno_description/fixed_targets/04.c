#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "http_parser.h"

extern "C" {
#include "http_parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int error_code = provider.ConsumeIntegral<int>();
  const char * error_description = http_errno_description((enum http_errno) error_code);
  if (error_description) {
    printf("%s\n", error_description);
  }
  return 0;
}