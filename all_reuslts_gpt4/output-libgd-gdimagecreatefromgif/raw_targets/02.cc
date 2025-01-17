#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "gd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write data to it
  FILE *fp = tmpfile();
  if (!fp) {
    return 0;
  }
  fwrite(data, 1, size, fp);
  rewind(fp);

  // Call the target function
  gdImagePtr im = gdImageCreateFromGif(fp);

  // Cleanup
  if (im) {
    gdImageDestroy(im);
  }
  fclose(fp);

  return 0;
}