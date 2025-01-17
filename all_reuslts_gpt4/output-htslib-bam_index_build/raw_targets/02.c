#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "bam.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for filename. We need to make sure it's null-terminated.
  std::string filename = stream.ConsumeRandomLengthString();
  filename.push_back('\0');

  // Extract an integer for min_shift
  int min_shift = stream.ConsumeIntegral<int>();

  // Call the target function
  int result = bam_index_build(filename.c_str(), min_shift);

  return 0;
}