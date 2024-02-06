#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <lcms2.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  char *cFileName = new char[size + 1];
  memcpy(cFileName, data, size);
  cFileName[size] = '\0';

  char *result = cmsCreateDeviceLinkFromCubeFile(cFileName);
  delete[] cFileName;
  free(result);

  return 0;
}