#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "myanmartools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *rawData, size_t length) {
  auto data = reinterpret_cast<const char *>(rawData);
  struct GMTZawgyiDetector *detector = GMTOpenZawgyiDetector();
  if (detector == nullptr) {
    return 0;
  }
  GMTZawgyiDetectorDetect(detector, data, length);
  GMTCloseZawgyiDetector(detector);
  return 0; // Non-zero return values are reserved for future use.
}