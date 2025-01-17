#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "htslib/sam.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the filename
  std::string filename = stream.ConsumeRandomLengthString();
  
  // Create a temporary file with the fuzzed data
  FILE* tmp = tmpfile();
  if (!tmp) {
    return 0;
  }
  fwrite(filename.c_str(), 1, filename.size(), tmp);
  fflush(tmp);

  // Get the name of the temporary file
  char fn[256];
  snprintf(fn, sizeof(fn), "/proc/self/fd/%d", fileno(tmp));

  // Extract an integer for min_shift
  int min_shift = stream.ConsumeIntegral<int>();

  // Call the target function
  int ret = bam_index_build(fn, min_shift);

  // Close the temporary file
  fclose(tmp);

  return 0;
}