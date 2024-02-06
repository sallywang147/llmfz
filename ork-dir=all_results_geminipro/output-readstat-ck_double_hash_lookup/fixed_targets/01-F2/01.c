#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "ck_hash.h"
#include "ck_md5.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const double key = stream.ConsumeFloatingPoint<double>();
  struct ck_hash_table_s* table = ck_hash_init(CK_MD5_HASH);
  char* result = ck_double_hash_lookup(key, table);
  ck_hash_destroy(table);
  free(result);
  return 0;
}
```

In this case, the issue was that the `ck_hash.h` and `ck_md5.h` headers were not wrapped in `extern "C" {}`. This is necessary because these headers are written in C, and the C++ compiler expects C++ headers. By wrapping them in `extern "C" {}`, we tell the compiler to treat them as C headers.