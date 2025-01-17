#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "gdbm.h"
}

int gdbm_load_from_file(struct gdbm_file_info**, FILE*, int, int, size_t*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int replace = stream.ConsumeIntegral<int>();
  const int meta_mask = stream.ConsumeIntegral<int>();
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  FILE* fp = fopen(filename.c_str(), "rb");
  if (fp == nullptr) {
    return 0;
  }
  struct gdbm_file_info* pdbf = nullptr;
  size_t line = 0;
  const int ret = gdbm_load_from_file(&pdbf, fp, replace, meta_mask, &line);
  fclose(fp);
  gdbm_close(pdbf);
  return ret;
}