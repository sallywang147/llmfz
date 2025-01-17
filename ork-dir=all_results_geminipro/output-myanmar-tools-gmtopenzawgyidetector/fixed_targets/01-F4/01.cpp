#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "zawgyi_detector.h"
}

struct GMTZawgyiDetector *GMTOpenZawgyiDetector() {
  return gmt_open_zawgyi_detector();
}

void GMTCloseZawgyiDetector(struct GMTZawgyiDetector *detector) {
  gmt_close_zawgyi_detector(detector);
}

int GMTIsZawgyi(struct GMTZawgyiDetector *detector, const char *text,
                size_t len) {
  return gmt_is_zawgyi(detector, text, len);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz(data, size);
  struct GMTZawgyiDetector *detector = GMTOpenZawgyiDetector();
  std::string text = fuzz.ConsumeRandomLengthString(1024);
  GMTIsZawgyi(detector, text.c_str(), text.size());
  GMTCloseZawgyiDetector(detector);
  return 0;
}