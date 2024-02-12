 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto input = provider.ConsumeRemainingBytesAsString();
  FILE* file = fmemopen((void*)input.c_str(), input.size(), "r");
  if (file == nullptr) {
    return 0;
  }
  struct gdbm_file_info* db = nullptr;
  size_t line = 0;
  int ret = gdbm_load_from_file(&db, file, 0, 0, &line);
  if (ret != 0) {
    return 0;
  }
  gdbm_close(db);
  return 0;
}