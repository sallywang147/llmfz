#include <stdint.h>
#include <stdlib.h>

#include "siphash.h"

extern "C" {
#include "llvm/Support/CommandLine.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  // Set the hash salt using siphash to generate a deterministic hash.
  struct sipkey key = sip_keyof(data);
  sip24_valid(&key);
  return 0;
}