#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "mutate.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct param p;
  const int seed = stream.ConsumeIntegral<int>();
  const int flags = stream.ConsumeIntegral<int>();
  mutate(&p, seed, flags);
  return 0;
}
```

The fixed code includes the `mutate.h` header and wraps the `#include "mutate.h"` directive with `extern "C" {}`. This ensures that the C++ compiler generates the correct linkage for the `mutate` function.

With these changes, the code should compile and run successfully.