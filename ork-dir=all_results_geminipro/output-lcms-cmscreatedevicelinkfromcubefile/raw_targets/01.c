#include "lcms2.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string cFileName = stream.ConsumeBytesAsString(size);
  char *ptr = cFileName.c_str();

  // Call the function to fuzz
  char *result = cmsCreateDeviceLinkFromCubeFile(ptr);
  free(result);

  return 0;
}