#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

size_t LLVMFuzzerCustomMutator(char *Data, size_t Size, size_t MaxSize, int Seed) {
  // Do something with Data, Size, MaxSize, and Seed.
  return Size;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  // Do something with Data and Size.
  LLVMFuzzerCustomMutator((char *)Data, Size, Size, 0);
  return 0;
}