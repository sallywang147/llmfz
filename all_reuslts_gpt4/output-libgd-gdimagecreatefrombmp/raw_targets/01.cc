#include <fuzzer/FuzzedDataProvider.h>
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a temporary file and write the data into it.
  FILE *fp = tmpfile();
  if (!fp) {
    return 0;
  }
  fwrite(data, 1, size, fp);
  rewind(fp);

  // Call the function to be fuzzed.
  gdImagePtr im = gdImageCreateFromBmp(fp);

  // Cleanup.
  if (im) {
    gdImageDestroy(im);
  }
  fclose(fp);
  return 0;
}