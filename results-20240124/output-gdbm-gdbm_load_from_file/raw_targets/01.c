 #include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct gdbm_file_info *pdbf = nullptr;
  size_t line = 0;
  int replace = stream.ConsumeIntegral<int>();
  int meta_mask = stream.ConsumeIntegral<int>();
  FILE *fp = tmpfile();
  if (fp == nullptr) {
    return 0;
  }
  if (fwrite(data, 1, size, fp) != size) {
    return 0;
  }
  if (fseek(fp, 0, SEEK_SET) != 0) {
    return 0;
  }
  gdbm_load_from_file(&pdbf, fp, replace, meta_mask, &line);
  fclose(fp);
  return 0;
}