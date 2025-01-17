#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" {
#include "scanContentNS.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  char* ptr = const_cast<char*>(provider.ConsumeRemainingBytes());
  char* end = ptr + size;
  char* nextTokPtr;

  struct encoding enc;
  memset(&enc, 0, sizeof(enc));

  int ret = initScanContentNS(&enc, ptr, end, &nextTokPtr);
  if (ret == 0) {
    printf("initScanContentNS returned 0\n");
  } else if (ret == 1) {
    printf("initScanContentNS returned 1\n");
  } else {
    printf("initScanContentNS returned %d\n", ret);
  }

  return 0;
}
```

The code above should build successfully without any errors.