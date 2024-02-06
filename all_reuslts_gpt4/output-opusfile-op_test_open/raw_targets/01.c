#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int ret;
  FuzzedDataProvider stream(data, size);

  // Creating a OggOpusFile object from the fuzzed data
  OggOpusFile *of = op_open_memory(data, size, &ret);
  if (!of)
    return 0;

  // Calling the function to fuzz
  ret = op_test_open(of);

  // Cleaning up
  op_free(of);
  return 0;
}