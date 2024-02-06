#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lcms2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a temporary file and write the fuzzed data to it.
  char filename[] = "/tmp/lcms_fuzz.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE* file = fdopen(fd, "wb");
  if (!file) {
    close(fd);
    return 0;
  }
  std::string fuzzed_data = provider.ConsumeRemainingBytesAsString();
  fwrite(fuzzed_data.data(), 1, fuzzed_data.size(), file);
  fclose(file);

  // Now we can call the function with the filename.
  char* result = cmsCreateDeviceLinkFromCubeFile(filename);

  // Clean up: Delete the temporary file and free the result.
  remove(filename);
  if (result) {
    free(result);
  }

  return 0;
}