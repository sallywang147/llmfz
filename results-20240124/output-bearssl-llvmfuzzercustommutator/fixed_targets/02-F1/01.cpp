#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char *data, size_t size,
                                         size_t max_size, int seed) {
  // Your custom mutator logic goes here.
  // For example, you can use the following code to randomly flip bits in the input:
  for (size_t i = 0; i < size; i++) {
    if (rand() % 2 == 0) {
      data[i] ^= 1;
    }
  }

  // Return the new size of the input.
  return size;
}