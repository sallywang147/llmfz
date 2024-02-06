#include <cstddef>
#include <cstdint>

#include "GMTZawgyiDetector.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct GMTZawgyiDetector *detector = GMTOpenZawgyiDetector();
  if (detector != nullptr) {
    // The function was called successfully.
    // Any additional fuzzing logic would go here.
  }
  return 0;
}