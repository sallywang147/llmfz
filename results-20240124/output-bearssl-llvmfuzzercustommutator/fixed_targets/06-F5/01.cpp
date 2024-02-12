#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "llvm/FuzzMutate.h"
}

size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize,
                               unsigned int Seed, unsigned int Flags) {
  // Do something interesting with Data, Size, MaxSize, Seed and Flags.
  return 0;
}