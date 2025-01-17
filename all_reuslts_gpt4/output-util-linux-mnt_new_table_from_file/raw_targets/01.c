#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libmount/libmount.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  
  struct libmnt_table *table = mnt_new_table_from_file(const_cast<char*>(filename.c_str()));
  
  if (table != nullptr) {
    mnt_free_table(table);
  }

  return 0;
}