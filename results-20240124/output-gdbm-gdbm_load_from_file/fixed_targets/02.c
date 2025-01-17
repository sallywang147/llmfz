 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct gdbm_file_info *pdbf;
  struct _IO_FILE *fp;
  int replace = provider.ConsumeBool();
  int meta_mask = provider.ConsumeIntegral<int>();
  size_t line;

  fp = tmpfile();
  if (fp == nullptr) {
    return 0;
  }

  if (fwrite(data, 1, size, fp) != size) {
    fclose(fp);
    return 0;
  }

  fseek(fp, 0, SEEK_SET);

  gdbm_load_from_file(&pdbf, fp, replace, meta_mask, &line);
  fclose(fp);

  return 0;
}