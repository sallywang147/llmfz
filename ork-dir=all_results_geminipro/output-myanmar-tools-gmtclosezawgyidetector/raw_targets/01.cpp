#include <cstddef>
#include <cstdint>

#include "public/myanmartools.h"

using google_myanmar_tools::ZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *rawData, size_t length) {
  auto data = reinterpret_cast<const char *>(rawData);
  ZawgyiDetector zawgyiDetector;
  zawgyiDetector.GetZawgyiProbability(data, length);
  GMTCloseZawgyiDetector(zawgyiDetector.GetZawgyiDetector());
  return 0; // Non-zero return values are reserved for future use.
}