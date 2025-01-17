#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "libFuzzer/FuzzedDataProvider.h"

extern "C" {
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1 << 20));
  void *data_ptr = bytes.data();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1 << 20));
  char *fn = str.c_str();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str2 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1 << 20));
  char *fnidx = str2.c_str();

  // Extract integral values
  int min_shift = stream.ConsumeIntegral<int>();
  int nthreads = stream.ConsumeIntegral<int>();

  sam_index_build3(fn, fnidx, min_shift, nthreads);

  return 0;
}