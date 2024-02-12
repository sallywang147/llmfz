#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "bam.h"

extern "C" {
#include "htslib/hts.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const std::string filename = provider.ConsumeRemainingBytesAsString();
  const int min_shift = provider.ConsumeIntegral<int>();

  return bam_index_build(const_cast<char*>(filename.c_str()), min_shift);
}