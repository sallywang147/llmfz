#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <htslib/sam.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a random file name
  std::string fn = stream.ConsumeRandomLengthString(16);
  std::string fnidx = stream.ConsumeRandomLengthString(16);

  // Generate random values for min_shift and nthreads
  int min_shift = stream.ConsumeIntegral<int>();
  int nthreads = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  int ret = sam_index_build3((char *)fn.c_str(), (char *)fnidx.c_str(), min_shift, nthreads);

  // Check the return value
  if (ret != 0) {
    fprintf(stderr, "sam_index_build3() failed with error code %d\n", ret);
    abort();
  }

  return 0;
}