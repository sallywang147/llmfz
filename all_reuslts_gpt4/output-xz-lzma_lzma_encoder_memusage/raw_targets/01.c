#include "fuzz_common.h"
#include "lzma.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string options_str = stream.ConsumeBytesAsString(stream.remaining_bytes());
  char *options = const_cast<char*>(options_str.c_str());

  // Call the target function
  size_t memusage = lzma_lzma_encoder_memusage(options);

  return 0;
}