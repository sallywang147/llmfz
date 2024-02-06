#include <stddef.h>
#include <stdint.h>

#include "apfs/apfs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  APFSFSCompat fs;
  char result;

  result = fs.istat(&fs, 0, nullptr, 0, 0, 0);

  return 0;
}