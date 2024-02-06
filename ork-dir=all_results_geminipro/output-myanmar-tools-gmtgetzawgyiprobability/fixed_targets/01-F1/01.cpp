#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "public/myanmartools.h"

extern "C" {
#include "third_party/icu/source/common/unicode/utypes.h"
}

using google_myanmar_tools::GMTZawgyiDetector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  GMTZawgyiDetector detector;
  std::string input = stream.ConsumeRemainingBytesAsString();

  double result = GMTGetZawgyiProbability(&detector, const_cast<char *>(input.c_str()));
  (void)result;  // Avoid unused variable warning.
  return 0;
}