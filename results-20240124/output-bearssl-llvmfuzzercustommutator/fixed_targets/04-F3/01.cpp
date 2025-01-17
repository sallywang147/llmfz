#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "llvm/FuzzMutate.h"
}

size_t LLVMFuzzerCustomMutator(char *Data, size_t Size, size_t MaxSize,
                               int Seed) {
  FuzzedDataProvider DataProvider(Data, Size);
  return llvm::mutate(DataProvider.ConsumeString(MaxSize), MaxSize, Seed);
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  LLVMFuzzerCustomMutator((char *)Data, Size, Size, 0);
  return 0;
}