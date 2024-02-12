 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char *data, size_t size,
                                         size_t max_size, int seed) {
  static bool initialized = false;
  if (!initialized) {
    srand(seed);
    initialized = true;
  }

  // Mutate the input data.
  for (size_t i = 0; i < size; i++) {
    data[i] = (uint8_t)(rand() % 256);
  }

  // Resize the input data to a random size.
  size = (rand() % (max_size - size)) + size;

  // Return the new size of the input data.
  return size;
}