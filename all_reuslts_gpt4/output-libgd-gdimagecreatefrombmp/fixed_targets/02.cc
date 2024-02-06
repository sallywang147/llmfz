#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "gd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data to it.
  FILE* file = tmpfile();
  if (!file) {
    return 0;
  }
  fwrite(data, 1, size, file);
  rewind(file);

  // Call the function to be tested.
  gdImagePtr image = gdImageCreateFromBmp(file);

  // Clean up.
  if (image) {
    gdImageDestroy(image);
  }
  fclose(file);

  return 0;
}