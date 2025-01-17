#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libmount/libmount.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct libmnt_table *tb = mnt_new_table();
  struct libmnt_table *u_tb = mnt_new_table();
  if (tb == nullptr || u_tb == nullptr) {
    mnt_unref_table(tb);
    mnt_unref_table(u_tb);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string filename = provider.ConsumeRandomLengthString();
  __mnt_table_parse_mountinfo(tb, const_cast<char*>(filename.c_str()), u_tb);

  mnt_unref_table(tb);
  mnt_unref_table(u_tb);

  return 0;
}