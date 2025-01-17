#include <fuzzer/FuzzedDataProvider.h>
#include "Poco/RegularExpression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }
  
  FuzzedDataProvider fuzzed_data(data, size);

  std::string regex_str = fuzzed_data.ConsumeRandomLengthString();
  std::string subject_str = fuzzed_data.ConsumeRemainingBytesAsString();
  
  try {
    Poco::RegularExpression regex(regex_str);
    std::string result_str;
    int options = 0;  // No options
    size_t pos = 0;   // Start of the string

    regex.substOne(&regex, &subject_str, pos, &result_str, options);
  } catch (...) {
    // Ignore exceptions, we're fuzzing
  }

  return 0;
}