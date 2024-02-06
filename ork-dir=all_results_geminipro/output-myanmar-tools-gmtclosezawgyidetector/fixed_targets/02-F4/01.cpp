#include <cstddef>

extern "C" {
#include "public/myanmartools.h"
}

using google_myanmar_tools::ZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *rawData, size_t length) {
  auto data = reinterpret_cast<const char *>(rawData);
  struct GMTZawgyiDetector *detector = GMTNewZawgyiDetector();
  GMTDetectZawgyi(detector, data, length);
  GMTDeleteZawgyiDetector(detector);  // Fix: Use GMTDeleteZawgyiDetector instead of GMTCloseZawgyiDetector
  return 0; // Non-zero return values are reserved for future use.
}
```

The corrected code uses `GMTDeleteZawgyiDetector` to delete the Zawgyi detector, which fixes the build error and ensures that the Zawgyi detector is properly cleaned up after use.