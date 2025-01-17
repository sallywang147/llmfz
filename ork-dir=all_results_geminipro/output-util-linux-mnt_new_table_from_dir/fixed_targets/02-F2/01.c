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
  const std::string dir_name = stream.ConsumeRemainingBytesAsString();
  mnt_new_table_from_dir(const_cast<char*>(dir_name.c_str()));
  return 0;
}