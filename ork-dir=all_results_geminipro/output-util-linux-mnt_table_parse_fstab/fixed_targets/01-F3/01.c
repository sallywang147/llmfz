#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <mntent.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  struct libmnt_table* table = mnt_init_table();
  int ret = mnt_table_parse_fstab(table, const_cast<char*>(filename.c_str()));
  mnt_free_table(table);
  return ret;
}