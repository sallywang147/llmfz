#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz_zip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *handle = nullptr;
  size_t cd_pos = stream.ConsumeIntegral<size_t>();

  mz_zip_goto_entry(handle, cd_pos);

  return 0;
}