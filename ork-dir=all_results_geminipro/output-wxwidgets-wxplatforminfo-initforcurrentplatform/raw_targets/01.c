#include "wx/platform.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  wxPlatformInfo platform_info;
  platform_info.InitForCurrentPlatform();
  return 0;
}