#include <stddef.h>
#include <stdint.h>

#include "apfs_compat.h"

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  APFSPoolCompat pool;
  if (!pool.open(data, size)) {
    return 0;
  }
  char result = pool.poolstat(nullptr);
  pool.close();
  return 0;
}