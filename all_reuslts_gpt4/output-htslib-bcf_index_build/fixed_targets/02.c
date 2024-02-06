#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "htslib/vcf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  int min_shift = stream.ConsumeIntegral<int>();

  FILE* file = fopen(filename.c_str(), "wb");
  if (!file) {
    return 0;
  }
  fclose(file);

  bcf_index_build(filename.c_str(), min_shift);

  remove(filename.c_str());

  return 0;
}