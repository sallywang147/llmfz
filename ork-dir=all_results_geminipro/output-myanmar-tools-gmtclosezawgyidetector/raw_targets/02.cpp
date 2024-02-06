#include <cstddef>

#include "public/myanmartools.h"

using google_myanmar_tools::ZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *rawData, size_t length) {
  auto data = reinterpret_cast<const char *>(rawData);
  struct GMTZawgyiDetector *detector = GMTNewZawgyiDetector();
  GMTDetectZawgyi(detector, data, length);
  GMTCloseZawgyiDetector(detector);
  return 0; // Non-zero return values are reserved for future use.
}