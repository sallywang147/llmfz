#include <fuzzer/FuzzedDataProvider.h>
#include "lzma.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *options = const_cast<char*>(str.c_str());

  // Call the function with the fuzzed input
  size_t memUsage = lzma_lzma_encoder_memusage(options);

  return 0;
}