#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Poco/RegularExpression.h"

extern "C" {
#include "Poco/RegularExpression.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  std::string pattern = stream.ConsumeRemainingBytesAsString();
  std::string replacement = stream.ConsumeRemainingBytesAsString();

  Poco::RegularExpression regex(pattern);
  int result = regex.subst(&input_string, 0, &replacement, 0);

  return 0;
}
```

The build error is caused by the following line:

```c++
#include "Poco/RegularExpression.h"
```

This line includes the header file `Poco/RegularExpression.h` twice, once in the global scope and once inside the `extern "C" {}` block. This is not allowed in C++, and it causes the linker to generate an error.

To fix the error, we need to remove the first `#include` directive and keep only the one inside the `extern "C" {}` block.

The corrected code:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "Poco/RegularExpression.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  std::string pattern = stream.ConsumeRemainingBytesAsString();
  std::string replacement = stream.ConsumeRemainingBytesAsString();

  Poco::RegularExpression regex(pattern);
  int result = regex.subst(&input_string, 0, &replacement, 0);

  return 0;
}