#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <libmount.h>

extern "C" {
#include <mntent.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  struct libmnt_table *tb = mnt_new_table();
  struct libmnt_table *u_tb = mnt_new_table();
  int ret = mnt_table_parse_mountinfo(tb, const_cast<char*>(filename.c_str()), u_tb);
  mnt_free_table(tb);
  mnt_free_table(u_tb);
  return ret;
}