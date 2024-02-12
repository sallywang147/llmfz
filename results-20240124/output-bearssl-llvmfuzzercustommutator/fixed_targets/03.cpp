#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "llvm/FuzzMutate.h"
}

extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize,
                               unsigned int Seed) {
  // Do some mutation here.
  return Size;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  // Do some fuzzing here.
  LLVMFuzzerMutate(Data, Size, Size, 0);
  return 0;
}