#include <stdint.h>
#include "wx/platinfo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  wxPlatformInfo pi;
  return 0;
}