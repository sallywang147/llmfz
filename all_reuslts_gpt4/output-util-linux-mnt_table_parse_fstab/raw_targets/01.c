#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libmount/libmount.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct libmnt_table *tb = mnt_new_table();
  if (tb == nullptr) {
    return 0;
  }

  std::string filename = stream.ConsumeRandomLengthString();
  mnt_table_parse_fstab(tb, const_cast<char*>(filename.c_str()));

  mnt_free_table(tb);

  return 0;
}