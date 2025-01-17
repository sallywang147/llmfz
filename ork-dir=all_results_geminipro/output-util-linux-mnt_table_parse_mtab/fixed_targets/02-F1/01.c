#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include <mntent.h>

extern "C" {
#include <mntent.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRemainingBytesAsString();
  struct libmnt_table* table = mnt_init_table();
  if (table == nullptr) {
    return 0;
  }
  int ret = mnt_table_parse_mtab(table, const_cast<char*>(filename.c_str()));
  mnt_free_table(table);
  return ret;
}