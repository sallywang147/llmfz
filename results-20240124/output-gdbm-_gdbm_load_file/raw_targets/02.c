 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t dump_file_size = provider.ConsumeIntegralInRange<size_t>(
      1, 1 << 20);
  std::vector<uint8_t> dump_file_buffer(dump_file_size);
  provider.ConsumeBytes<uint8_t>(dump_file_buffer.data(), dump_file_size);
  struct dump_file dump_file;
  dump_file.df_ptr = dump_file_buffer.data();
  dump_file.df_size = dump_file_size;

  struct gdbm_file_info dbf;
  struct gdbm_file_info* ofp = nullptr;
  const int replace = provider.ConsumeBool();
  const int meta_mask = provider.ConsumeIntegral<int>();
  int ret = _gdbm_load_file(&dump_file, &dbf, &ofp, replace, meta_mask);
  if (ret == 0) {
    gdbm_free_file_info(&dbf);
    gdbm_free_file_info(ofp);
  }
  return 0;
}