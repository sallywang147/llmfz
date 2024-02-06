#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <mntent.h>
#include <mnttab.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  struct libmnt_table* table = mnt_new_table();
  int ret = mnt_table_parse_mtab(table, const_cast<char*>(filename.c_str()));
  mnt_free_table(table);
  return ret;
}