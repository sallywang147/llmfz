 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <gdbm.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gdbm_init_library(nullptr);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  const std::string filename = provider.ConsumeRemainingBytesAsString();
  const int replace = provider.ConsumeIntegral<int>();
  const int meta_mask = provider.ConsumeIntegral<int>();
  size_t line = 0;

  struct gdbm_file_info* dbfile = nullptr;
  int ret = gdbm_load(&dbfile, const_cast<char*>(filename.c_str()), replace,
                       meta_mask, &line);
  if (ret == 0) {
    gdbm_close(dbfile);
  }

  return 0;
}