 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "http_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int error_code = provider.ConsumeIntegral<int>();
  char * error_description = http_errno_description(error_code);
  if (error_description) {
    printf("%s\n", error_description);
  }
  return 0;
}