#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libmount/libmount.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct libmnt_table* tb = mnt_new_table();
  if (!tb) {
    return 0;
  }

  std::string filename = stream.ConsumeRandomLengthString();
  FILE* f = fmemopen((void*)filename.c_str(), filename.size(), "r");
  if (!f) {
    mnt_free_table(tb);
    return 0;
  }

  mnt_table_parse_mtab(tb, filename.c_str());

  fclose(f);
  mnt_free_table(tb);

  return 0;
}