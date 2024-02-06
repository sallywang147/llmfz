#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sam.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract two strings for fn and fnidx parameters
  std::string fn = stream.ConsumeRandomLengthString();
  std::string fnidx = stream.ConsumeRemainingBytesAsString();

  // Extract an integer for min_shift parameter
  int min_shift = stream.ConsumeIntegral<int>();

  // Call the target function
  int result = sam_index_build2(const_cast<char*>(fn.c_str()), const_cast<char*>(fnidx.c_str()), min_shift);

  return 0;
}