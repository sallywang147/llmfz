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
  FuzzedDataProvider provider(data, size);

  struct gdbm_file_info* dbf = nullptr;
  struct gdbm_file_info ofp;  // Fix the type mismatch

  const int replace = provider.ConsumeIntegral<int>();
  const int meta_mask = provider.ConsumeIntegral<int>();

  const size_t filename_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  auto filename = provider.ConsumeBytes<char>(filename_size);
  struct dump_file* file = _gdbm_open_dump_file(filename.data(), "r");
  if (file == nullptr) {
    return 0;
  }

  int ret = _gdbm_load_file(file, &dbf, &ofp, replace, meta_mask);
  if (ret == 0) {
    _gdbm_close_dump_file(file);
    _gdbm_free_file_info(dbf);
    _gdbm_free_file_info(&ofp);  // Fix the type mismatch
  }
  return 0;
}