#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "htslib/hts.h"
#include "htslib/vcf.h"

#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a random filename.
  std::string filename = stream.ConsumeRandomLengthString(16);

  // Generate a random min_shift value.
  int min_shift = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed.
  int result = bcf_index_build((char *)filename.c_str(), min_shift);

  // Check the result.
  if (result != 0) {
    // An error occurred.
    abort();
  }

  return 0;
}