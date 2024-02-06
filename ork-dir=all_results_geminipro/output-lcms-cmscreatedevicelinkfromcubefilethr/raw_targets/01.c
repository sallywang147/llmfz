#include "lcms2.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 12) {
    return 0;
  }

  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  char *cFileName = (char *)data;

  cmsCreateDeviceLinkFromCubeFileTHR(ContextID, cFileName);

  cmsDeleteContext(ContextID);
  return 0;
}