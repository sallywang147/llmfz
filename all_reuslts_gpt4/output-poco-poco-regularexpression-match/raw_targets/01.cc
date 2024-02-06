#include <fuzzer/FuzzedDataProvider.h>
#include "Poco/RegularExpression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();
  std::string input = stream.ConsumeRemainingBytesAsString();

  Poco::RegularExpression regex(pattern);

  try {
    regex.match(input);
  } catch (...) {
    return 0;
  }

  return 0;
}