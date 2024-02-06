#include <fuzzer/FuzzedDataProvider.h>
#include "Poco/RegularExpression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }
  FuzzedDataProvider fuzzed_data(data, size);

  std::string pattern = fuzzed_data.ConsumeRandomLengthString();
  std::string input = fuzzed_data.ConsumeRandomLengthString();
  std::string replacement = fuzzed_data.ConsumeRemainingBytesAsString();

  try {
    Poco::RegularExpression re(pattern);
    int options = fuzzed_data.ConsumeIntegral<int>();
    re.subst(input, replacement, options);
  } catch (...) {
  }
  return 0;
}