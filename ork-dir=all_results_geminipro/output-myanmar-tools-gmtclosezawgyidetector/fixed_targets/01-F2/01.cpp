#include <cstddef>
#include <cstdint>

extern "C" {
#include "public/myanmartools.h"
}

using google_myanmar_tools::ZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ZawgyiDetector detector;
  detector.Open();
  // ...
  detector.Close();
  return 0;
}