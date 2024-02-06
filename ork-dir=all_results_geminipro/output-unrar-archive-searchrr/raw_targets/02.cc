#include <cstddef>
#include <cstdint>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "Archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Archive archive;
  size_t result = archive.SearchRR(&archive);
  return 0;
}