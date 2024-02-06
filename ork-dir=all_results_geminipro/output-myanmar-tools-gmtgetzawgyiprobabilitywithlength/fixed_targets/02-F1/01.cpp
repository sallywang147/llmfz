#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "public/myanmartools.h"

extern "C" {
#include "myanmartools/ZawgyiUnicodeData.h"
}

using google_myanmar_tools::GMTZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a GMTZawgyiDetector object.
  GMTZawgyiDetector detector;

  // Create a FuzzedDataProvider object to generate random inputs.
  FuzzedDataProvider stream(data, size);

  // Generate a random string of characters.
  std::string input_utf8 = stream.ConsumeRemainingBytesAsString();

  // Get the Zawgyi probability for the input string.
  double probability = GMTGetZawgyiProbabilityWithLength(
      &detector, const_cast<char *>(input_utf8.c_str()), input_utf8.size());

  // Do something with the probability.
  (void)probability;

  return 0;
}