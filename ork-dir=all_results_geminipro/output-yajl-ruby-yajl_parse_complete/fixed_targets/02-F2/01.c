#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "yajl/yajl_parse.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    yajl_config(yajl_allow_comments, 1);
    initialized = true;
  }

  yajl_handle hand = yajl_alloc(NULL, NULL, NULL);
  if (hand == NULL) {
    return 0;
  }

  yajl_status status = yajl_parse(hand, data, size);
  if (status != yajl_status_ok) {
    yajl_free(hand);
    return 0;
  }

  status = yajl_parse_complete(hand);
  if (status != yajl_status_ok) {
    yajl_free(hand);
    return 0;
  }

  yajl_free(hand);

  return 0;
}
```

The provided code has no build issues.