#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "gdbm-ndbm.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string filename = stream.ConsumeRemainingBytesAsString();
  struct gdbm_file_info* pdbf;
  int replace = stream.ConsumeBool() ? GDBM_REPLACE : GDBM_WRCREAT;
  int meta_mask = stream.ConsumeIntegral<int>();
  size_t line;

  int ret = gdbm_open(&pdbf, const_cast<char*>(filename.c_str()), replace, meta_mask,
                      &line);
  if (ret == 0) {
    gdbm_close(pdbf);
  } else {
    gdbm_load(&pdbf, const_cast<char*>(filename.c_str()), replace, meta_mask,
              &line);
  }

  return 0;
}