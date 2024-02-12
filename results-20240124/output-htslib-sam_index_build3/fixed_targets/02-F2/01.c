#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "../../htslib/sam.h"
}

#include <string>
#include <iostream>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  const std::string index_filename = stream.ConsumeRemainingBytesAsString();
  const int min_shift = stream.ConsumeIntegral<int>();
  const int nthreads = stream.ConsumeIntegral<int>();

  sam_index_build3(const_cast<char*>(filename.c_str()),
                   const_cast<char*>(index_filename.c_str()), min_shift,
                   nthreads);

  return 0;
}