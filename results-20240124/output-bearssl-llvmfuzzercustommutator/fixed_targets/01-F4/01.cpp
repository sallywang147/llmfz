#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"

int LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize,
                               unsigned int Seed) {
  // Do some mutation here.
  return Size;
}
}

extern "C" int LLVMFuzzerTestOneInput(uint8_t *Data, size_t Size) {
  LLVMFuzzerCustomMutator(Data, Size, Size, 0);
  return 0;
}