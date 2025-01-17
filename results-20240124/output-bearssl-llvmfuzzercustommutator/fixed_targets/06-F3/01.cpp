extern "C" {
#include <stddef.h>
#include <string.h>

size_t LLVMFuzzerCustomMutator(char *Data, size_t Size,
                                           size_t MaxSize, int Seed) {
  // Do something with Data, Size, MaxSize, and Seed.
  // Here we just copy the input data to the output.
  if (Size > MaxSize) {
    Size = MaxSize;
  }
  memcpy(Data, Data, Size);
  return Size;
}
}