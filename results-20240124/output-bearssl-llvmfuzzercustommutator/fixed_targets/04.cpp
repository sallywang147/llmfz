#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "llvm/FuzzMutate.h"
}

size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize,
                               unsigned int Seed) {
  FuzzedDataProvider DataProvider(Data, Size);
  // Mutate the input data.
  DataProvider.ConsumeBytes<uint8_t>(Size);
  // Return the new size of the data.
  return DataProvider.remaining_bytes();
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  // Call the custom mutator.
  LLVMFuzzerCustomMutator((uint8_t *)Data, Size, Size, 0);
  // Do something with the data.
  return 0;
}