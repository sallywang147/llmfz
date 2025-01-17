#include <fuzzer/FuzzedDataProvider.h>
#include "Poco/RegularExpression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string regex_str = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string target_str = stream.ConsumeRemainingBytesAsString();

  try {
    Poco::RegularExpression regex(regex_str);
    size_t offset = 0;
    int options = 0;
    regex.match(&regex, &target_str, offset, options);
  } catch (...) {
    // Ignore exceptions
  }

  return 0;
}