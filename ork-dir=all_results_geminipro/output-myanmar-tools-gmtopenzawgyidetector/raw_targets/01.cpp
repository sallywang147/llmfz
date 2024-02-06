#include <cstddef>
#include <cstdint>

#include "public/myanmartools.h"

using google_myanmar_tools::GMTZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *rawData, size_t length) {
  auto data = reinterpret_cast<const char *>(rawData);
  GMTZawgyiDetector *detector = GMTOpenZawgyiDetector();
  GMTDetectZawgyi(detector, data, length);
  GMTCloseZawgyiDetector(detector);
  return 0; // Non-zero return values are reserved for future use.
}