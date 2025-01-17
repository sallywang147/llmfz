 #include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/hfile.h"
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int min_shift = stream.ConsumeIntegral<int>();
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  const char *fn = filename.c_str();
  const std::string index_filename = stream.ConsumeRemainingBytesAsString();
  const char *fnidx = index_filename.c_str();

  sam_index_build2((char *)fn, (char *)fnidx, min_shift);
  return 0;
}