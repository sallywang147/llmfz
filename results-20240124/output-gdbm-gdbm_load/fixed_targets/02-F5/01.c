#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "gdbm.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gdbm_init_library();
    initialized = true;
  }
  FuzzedDataProvider provider(data, size);
  const std::string filename = provider.ConsumeRemainingBytesAsString();
  const int replace = provider.ConsumeBool();
  const int meta_mask = provider.ConsumeIntegral<int>();
  size_t line = 0;
  struct gdbm_file_info* db = nullptr;
  int ret = gdbm_load(&db, const_cast<char*>(filename.c_str()), replace, meta_mask, &line);
  if (db != nullptr) {
    gdbm_close(db);
  }
  return ret;
}