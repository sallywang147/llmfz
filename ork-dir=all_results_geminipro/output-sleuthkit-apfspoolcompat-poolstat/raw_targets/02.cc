#include <stddef.h>
#include <stdint.h>

#include "apfs_pool_compat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  APFSPoolCompat *pool = new APFSPoolCompat();
  pool->poolstat(nullptr);
  delete pool;
  return 0;
}