 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "llvm/ADT/StringRef.h"
#include "llvm/FuzzMutate/FuzzMutate.h"

extern "C" size_t LLVMFuzzerCustomMutator(char *Data, size_t Size,
                                          size_t MaxSize, int Seed) {
  llvm::StringRef DataRef(Data, Size);
  llvm::mutate(DataRef, MaxSize, Seed);
  return DataRef.size();
}