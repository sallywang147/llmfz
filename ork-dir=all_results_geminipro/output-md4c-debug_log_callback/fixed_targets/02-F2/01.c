#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" {
#include "debug_log_callback.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string log_message = stream.ConsumeRemainingBytesAsString();
  const std::string log_file = stream.ConsumeRemainingBytesAsString();
  debug_log_callback(log_message.c_str(), log_file.c_str());
  return 0;
}
```

The only issue with the original code is that the `debug_log_callback` function is called with `const` arguments, while the function expects non-`const` arguments. This can be fixed by casting the arguments to `char*` without the `const` qualifier.