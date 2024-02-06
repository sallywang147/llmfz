#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <mntent.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  struct libmnt_table* table = mnt_init_table();
  if (table == nullptr) {
    return 0;
  }

  int ret = mnt_table_parse_fstab(table, filename.c_str());
  mnt_free_table(table);
  return ret;
}
```

The issue is that the `mnt_table_parse_fstab` function takes a `const char*` as its second argument, but the code was passing a `char*`. To fix this, the code has been changed to pass `filename.c_str()` instead of `const_cast<char*>(filename.c_str())`.