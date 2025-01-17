#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize,
                               unsigned int Seed) {
  // Do some mutation here.
  return Size;
}

DEFINE_FUZZER(LLVMFuzzerTestOneInput, LLVMFuzzerCustomMutator)