#include "wx/platinfo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  wxPlatformInfo* platform_info = wxPlatformInfo::Get();
  return 0;
}