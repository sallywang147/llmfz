#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "Poco/RegularExpression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string pattern = provider.ConsumeRemainingBytesAsString();
  if (pattern.empty()) {
    return 0;
  }

  Poco::RegularExpression regex(pattern);
  std::string input = provider.ConsumeRemainingBytesAsString();
  std::string replace = provider.ConsumeRemainingBytesAsString();

  int num_replacements = provider.ConsumeIntegralInRange<int>(0, 100);
  regex.subst(&input, num_replacements, &replace,
              Poco::RegularExpression::Global);
  return 0;
}