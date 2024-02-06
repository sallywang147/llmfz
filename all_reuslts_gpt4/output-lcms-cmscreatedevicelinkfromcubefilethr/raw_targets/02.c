#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lcms2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a context
  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  if (ContextID == NULL) {
    return 0;
  }

  // Create a temporary file from the fuzzing input
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    cmsDeleteContext(ContextID);
    return 0;
  }
  FILE* file = fdopen(fd, "wb");
  if (file == NULL) {
    close(fd);
    remove(filename);
    cmsDeleteContext(ContextID);
    return 0;
  }

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(bytes.data(), 1, bytes.size(), file);
  fclose(file);

  // Call the function to fuzz
  char* result = cmsCreateDeviceLinkFromCubeFileTHR(ContextID, filename);

  // Clean up
  remove(filename);
  cmsDeleteContext(ContextID);
  if (result != NULL) {
    free(result);
  }

  return 0;
}