 #include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct gdbm_file_info *pdbf = nullptr;
  int replace = stream.ConsumeBool();
  int meta_mask = stream.ConsumeIntegral<int>();
  size_t line;
  std::string input = stream.ConsumeRemainingBytesAsString();
  auto fp = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
  gdbm_load_from_file(&pdbf, fp, replace, meta_mask, &line);
  fclose(fp);
  if (pdbf != nullptr) {
    gdbm_close(pdbf);
  }
  return 0;
}