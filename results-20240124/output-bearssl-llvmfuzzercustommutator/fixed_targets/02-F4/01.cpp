#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "llvm/Fuzz.h"
}

// Custom mutator for LLVMFuzzerTestOneInput.
// This mutator flips a single bit in the input buffer.
static size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size,
                                        size_t MaxSize) {
  FuzzedDataProvider DataProvider(Data, Size);
  // Flip a single bit in the input buffer.
  size_t Index = DataProvider.ConsumeIntegralInRange<size_t>(0, Size - 1);
  Data[Index] ^= 1;
  return Size;
}

// Entry point for the fuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  // Do something with the input data here.
  return 0;
}