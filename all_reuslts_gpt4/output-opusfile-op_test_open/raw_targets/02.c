#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create OggOpusFile from data
  int ret;
  OggOpusFile *of = op_open_memory(data, size, &ret);
  if (!of)
    return 0;

  // Call the function to be fuzzed
  ret = op_test_open(of);

  // Clean up
  op_free(of);
  return 0;
}