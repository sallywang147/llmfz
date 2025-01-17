 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gdbm_init();
    initialized = true;
  }
  FuzzedDataProvider provider(data, size);
  int ret;
  struct dump_file file;
  struct gdbm_file_info dbf;
  struct gdbm_file_info *ofp;
  int replace = provider.ConsumeIntegral<int>();
  int meta_mask = provider.ConsumeIntegral<int>();
  ret = _gdbm_load_file(&file, &dbf, &ofp, replace, meta_mask);
  return 0;
}