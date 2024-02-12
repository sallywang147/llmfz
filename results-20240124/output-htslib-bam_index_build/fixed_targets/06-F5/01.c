#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "htslib/hts.h"
#include "htslib/sam.h"

#include <string>
#include <iostream>
#include <sstream>

#include "libFuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::stringstream ss;
  ss << stream.ConsumeRemainingBytesAsString();
  std::string filename = ss.str();
  char* filename_ptr = const_cast<char*>(filename.c_str());
  int min_shift = stream.ConsumeIntegral<int>();
  bam_index_build(filename_ptr, min_shift);
  return 0;
}