#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char *data, size_t size, size_t max_size, int seed) {
  // Use the seed to initialize the random number generator.
  srand(seed);

  // Generate a random number between 0 and max_size.
  size_t new_size = rand() % (max_size + 1);

  // If the new size is smaller than the original size, then we need to
  // truncate the data.
  if (new_size < size) {
    data[new_size] = '\0';
  }
  // If the new size is larger than the original size, then we need to
  // pad the data with random bytes.
  else if (new_size > size) {
    for (size_t i = size; i < new_size; i++) {
      data[i] = rand() % 256;
    }
  }

  // Return the new size of the data.
  return new_size;
}