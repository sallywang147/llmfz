#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wx/platform.h"

extern "C" {
#include "wx/wx.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  wxPlatformInfo info;
  wxPlatformInfo::InitForCurrentPlatform(&info);  // Initialize the platform info
  wxPlatformInfo::Get(&info);

  return 0;
}