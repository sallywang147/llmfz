#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "htslib/vcf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the filename.
  std::string filename = stream.ConsumeRandomLengthString();
  // Extract an integer for the min_shift.
  int min_shift = stream.ConsumeIntegral<int>();

  // Create a temporary file and write the extracted string to it.
  FILE *tmpf = tmpfile();
  if (!tmpf) {
    return 0;
  }
  fwrite(filename.c_str(), 1, filename.size(), tmpf);
  fflush(tmpf);

  // Get the filename of the temporary file.
  char fn[L_tmpnam];
  if (tmpnam(fn) == NULL) {
    fclose(tmpf);
    return 0;
  }

  // Rename the temporary file to the generated filename.
  if (rename(tmpnam(NULL), fn) != 0) {
    fclose(tmpf);
    return 0;
  }

  // Call the target function.
  int ret = bcf_index_build(fn, min_shift);

  // Clean up.
  fclose(tmpf);
  remove(fn);

  return 0;
}