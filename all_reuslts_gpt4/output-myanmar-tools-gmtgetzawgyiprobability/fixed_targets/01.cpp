#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "GMTZawgyiDetector.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string input_utf8 = stream.ConsumeRemainingBytesAsString();

  GMTZawgyiDetector* detector = GMTZawgyiDetector_New();
  if (!detector) {
    return 0;
  }

  double probability = GMTGetZawgyiProbability(detector, const_cast<char*>(input_utf8.c_str()));

  GMTZawgyiDetector_Delete(detector);

  return 0;
}