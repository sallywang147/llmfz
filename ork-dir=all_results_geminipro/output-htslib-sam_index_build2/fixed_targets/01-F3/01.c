#include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "../../htslib/sam.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string fn = stream.ConsumeRandomLengthString();
  char *fn_ptr = fn.c_str();

  std::string fnidx = stream.ConsumeRandomLengthString();
  char *fnidx_ptr = fnidx.c_str();

  int min_shift = stream.ConsumeIntegral<int>();

  int ret = sam_index_build2(fn_ptr, fnidx_ptr, min_shift);

  if (ret < 0) {
    fprintf(stderr, "sam_index_build2 failed with error code %d\n", ret);
    return 1;
  }

  return 0;
}