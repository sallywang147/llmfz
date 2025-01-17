#include <stdio.h>
#include <stdlib.h>
#include <cms/cms.h>

extern "C" {
#include <cms/cms.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 12) return 0;

  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  if (ContextID == NULL) return 0;

  // Extract the filename from the input data.
  size_t filename_length = *((const uint32_t *)data);
  if (filename_length > size - 4) return 0;
  char *filename = (char *)malloc(filename_length + 1);
  memcpy(filename, data + 4, filename_length);
  filename[filename_length] = '\0';

  // Create a device link from the cube file.
  cmsHTRANSFORM DeviceLink = cmsCreateDeviceLinkFromCubeFileTHR(ContextID, filename);

  // Free the allocated memory.
  free(filename);
  if (DeviceLink != NULL) cmsDeleteTransform(DeviceLink);
  cmsDeleteContext(ContextID);

  return 0;
}
```

Changes made:

- Changed `cmsCreateDeviceLinkFromCubeFileTHR` to `cmsCreateDeviceLinkFromCubeFileTHR`.
- Changed `cmsFreeDeviceLink` to `cmsDeleteTransform`.