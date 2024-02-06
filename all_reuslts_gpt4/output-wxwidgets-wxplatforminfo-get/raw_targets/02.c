#include "wx/platinfo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // We don't really use the input data here, because the function doesn't take any parameters.
  // But a fuzzer might still find a bug in the function itself.
  wxPlatformInfo* info = wxPlatformInfo::Get();

  // Do something with the info to make sure the function is not optimized away.
  // We don't actually care about the output, so we just ignore it.
  (void)info->GetOperatingSystemId();

  return 0;
}