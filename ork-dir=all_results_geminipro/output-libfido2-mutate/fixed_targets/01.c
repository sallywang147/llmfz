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

Changes made:

1. Added `extern "C" {}` around the `#include "mutate.h"` directive to ensure proper linkage for the `mutate` function.
2. Removed the `#include <cstdio>` directive since it is not used in the code.