#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "Poco/RegularExpression.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();
  if (input.empty()) {
    return 0;
  }
  std::string pattern = provider.ConsumeRemainingBytesAsString();
  if (pattern.empty()) {
    return 0;
  }
  std::string replacement = provider.ConsumeRemainingBytesAsString();
  if (replacement.empty()) {
    return 0;
  }
  Poco::RegularExpression regex(pattern);
  size_t offset = provider.ConsumeIntegralInRange<size_t>(0, input.size());
  regex.substOne(&input, offset, replacement);  // Corrected the call to substOne
  return 0;
}
```

Changes made:

1. Added checks for empty input, pattern, and replacement strings to handle cases where the provider does not provide any data.
2. Corrected the `regex.substOne` call to use the correct overload that takes the offset as the third argument.