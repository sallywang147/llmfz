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
  const size_t filename_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  const std::string filename = provider.ConsumeBytesAsString(filename_size);
  const int replace = provider.ConsumeBool();
  const int meta_mask = provider.ConsumeIntegral<int>();
  size_t line = 0;
  struct gdbm_file_info* pdbf = nullptr;
  gdbm_load(&pdbf, const_cast<char*>(filename.c_str()), replace, meta_mask, &line);
  gdbm_close(pdbf);
  return 0;
}