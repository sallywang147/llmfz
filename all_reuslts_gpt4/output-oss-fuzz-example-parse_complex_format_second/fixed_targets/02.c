#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "complex_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzedDataProvider(data, size);
  std::string input = fuzzedDataProvider.ConsumeRemainingBytesAsString();
  
  parse_complex_format_second(input.c_str());

  return 0;
}