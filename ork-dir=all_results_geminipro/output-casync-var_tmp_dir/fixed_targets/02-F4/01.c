#include <fuzzer/FuzzedDataProvider.h>
#include <var_tmp_dir.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include <var_tmp_dir.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string path = provider.ConsumeRandomLengthString(1024);
  char* ret = nullptr;
  int result = var_tmp_dir(&ret);
  if (result == 0) {
    free(ret);
  }
  return 0;
}
```
The provided code has no build issues.