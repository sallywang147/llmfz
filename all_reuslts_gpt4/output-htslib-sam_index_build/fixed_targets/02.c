#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sam.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *fn = const_cast<char*>(str.c_str());

  // Extract integral values
  int min_shift = stream.ConsumeIntegral<int>();

  // Call the function under test
  int result = sam_index_build(fn, min_shift);

  return 0;
}