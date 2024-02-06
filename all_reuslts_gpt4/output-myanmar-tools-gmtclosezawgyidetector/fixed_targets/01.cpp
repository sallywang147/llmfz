#include <cstddef>
#include <cstdint>

#include "public/myanmartools.h"

using google_myanmar_tools::ZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ZawgyiDetector* detector = new ZawgyiDetector();
  GMTCloseZawgyiDetector(detector);
  return 0; // Non-zero return values are reserved for future use.
}