#include <cstddef>

#include "public/myanmartools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct GMTZawgyiDetector * detector = GMTOpenZawgyiDetector();
  if (detector != nullptr) {
    GMTCloseZawgyiDetector(detector);
  }
  return 0; // Non-zero return values are reserved for future use.
}