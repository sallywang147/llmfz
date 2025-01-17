#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <mntent.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string dirname = stream.ConsumeRemainingBytesAsString();
  mnt_new_table_from_dir(const_cast<char*>(dirname.c_str()));
  return 0;
}