#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
size_t LLVMFuzzerCustomMutator(char *data, size_t size,
                                         size_t max_size, int seed) {
  static bool initialized = false;
  if (!initialized) {
    srand(seed); // Include <cstdlib> for this function
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
}

int main() {
  // Create a vector of data to be mutated.
  std::vector<uint8_t> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Call the custom mutator function to mutate the data.
  size_t new_size = LLVMFuzzerCustomMutator(data.data(), data.size(),
                                             data.max_size(), 42);

  // Print the mutated data.
  for (size_t i = 0; i < new_size; i++) {
    printf("%d ", data[i]);
  }
  printf("\n");

  return 0;
}