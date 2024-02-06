#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "GMTZawgyiDetector.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  // Create a GMTZawgyiDetector instance
  struct GMTZawgyiDetector* detector = GMTZawgyiDetector_new();

  // Get the input string for the detector
  std::string input_utf8 = stream.ConsumeRemainingBytesAsString();

  // Call the function to be fuzzed
  double probability = GMTGetZawgyiProbability(detector, const_cast<char*>(input_utf8.c_str()));

  // Clean up
  GMTZawgyiDetector_delete(detector);

  return 0;
}