#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <gd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data to it.
  FILE* tmp = tmpfile();
  if (!tmp) {
    return 0;
  }
  fwrite(data, 1, size, tmp);
  rewind(tmp);

  // Call the function to be fuzzed.
  gdImagePtr im = gdImageCreateFromGif(tmp);

  // Clean up.
  if (im) {
    gdImageDestroy(im);
  }
  fclose(tmp);

  return 0;
}