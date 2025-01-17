#include <lcms2.h>
#include <cstring>
#include <string>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

#include <lcms2_plugin.h>  // Include the necessary header file for cmsCloseProfile

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string cFileName = stream.ConsumeBytesAsString(size);
  char *ptr = cFileName.c_str();

  // Call the function to fuzz
  cmsHPROFILE result = cmsCreateDeviceLinkFromCubeFile(ptr);
  if (result != NULL) {
    cmsCloseProfile(result);
  }

  return 0;
}