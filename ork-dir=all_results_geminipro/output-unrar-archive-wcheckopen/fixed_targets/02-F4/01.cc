#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "archive.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Archive archive;
  bool success = archive.WCheckOpen(const_cast<int *>(stream.ConsumeIntegral<int *>()),
                                  stream.ConsumeRemainingBytes());
  if (success) {
    archive.Close();
  }
  return 0;
}
```
The `stdlib.h` header was also included to fix the `malloc` function call.