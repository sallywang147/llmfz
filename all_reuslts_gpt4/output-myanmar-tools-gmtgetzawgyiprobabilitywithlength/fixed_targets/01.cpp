#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "GMTZawgyiDetector.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);

  // Create a new detector
  struct GMTZawgyiDetector* detector = GMTNewZawgyiDetector();

  // Consume the data as a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* input_utf8 = const_cast<char*>(str.c_str());
  int length = static_cast<int>(str.size());

  // Call the function to fuzz
  double result = GMTGetZawgyiProbabilityWithLength(detector, input_utf8, length);

  // Free the detector
  GMTDeleteZawgyiDetector(detector);

  return 0;
}