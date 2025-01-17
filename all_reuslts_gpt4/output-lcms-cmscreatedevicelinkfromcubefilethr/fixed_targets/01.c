#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lcms2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file with the fuzzed data
  char filename[] = "/tmp/fuzzedfileXXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE* file = fdopen(fd, "wb");
  if (!file) {
    close(fd);
    return 0;
  }
  std::vector<uint8_t> fuzzed_data = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(fuzzed_data.data(), 1, fuzzed_data.size(), file);
  fclose(file);

  // Create the context
  cmsContext ContextID = cmsCreateContext(NULL, NULL);

  // Call the function to fuzz
  char* result = cmsCreateDeviceLinkFromCubeFileTHR(ContextID, filename);

  // Cleanup
  cmsDeleteContext(ContextID);
  remove(filename);
  free(result);

  return 0;
}