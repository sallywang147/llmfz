 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int replace = stream.ConsumeIntegral<int>();
  const int meta_mask = stream.ConsumeIntegral<int>();
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  struct dump_file file;
  struct gdbm_file_info dbf;
  struct gdbm_file_info* ofp = nullptr;

  _gdbm_load_file(&file, &dbf, &ofp, replace, meta_mask);

  return 0;
}