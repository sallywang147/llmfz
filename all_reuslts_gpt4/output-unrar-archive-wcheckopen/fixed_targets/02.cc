#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "Archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Archive archive;
  int name = stream.ConsumeIntegral<int>();

  archive.WCheckOpen(&archive, &name);

  return 0;
}