#include <config.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/hfile.h"
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

extern "C" {
#include "htslib/kstring.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *fn = stream.ConsumeRandomLengthString().c_str();
  char *fnidx = stream.ConsumeRandomLengthString().c_str();
  int min_shift = stream.ConsumeIntegral<int>();

  int ret = sam_index_build3(fn, fnidx, min_shift);
  if (ret != 0)
    abort();

  ret = sam_index_build2(fn, fnidx, min_shift);
  if (ret != 0)
    abort();

  return 0;
}