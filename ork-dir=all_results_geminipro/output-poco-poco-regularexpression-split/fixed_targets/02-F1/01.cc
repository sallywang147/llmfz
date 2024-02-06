#include "Poco/RegularExpression.h"

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();
  std::string regex = provider.ConsumeRemainingBytesAsString();

  Poco::RegularExpression re(regex);
  std::vector<std::string> matches;
  re.split(input, matches);

  return 0;
}
```

The issue was that the `Poco/RegularExpression.h` header was not wrapped with `extern "C" {}`. This caused the linker to fail to find the definition of the `Poco::RegularExpression` class.

To fix this issue, the `#include` directive for `Poco/RegularExpression.h` was wrapped with `extern "C" {}`. This tells the compiler to treat the header as a C header, which allows the linker to find the definition of the `Poco::RegularExpression` class.