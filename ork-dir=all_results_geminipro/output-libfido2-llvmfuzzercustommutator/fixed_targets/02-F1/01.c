#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size,
                                         size_t max_size, int seed) {
  FuzzedDataProvider stream(data, size);

  // Use the seed to generate a random number between 0 and max_size.
  size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);

  // If the new size is smaller than the current size, copy the data from the
  // beginning of the input to the new buffer.
  if (new_size < size) {
    memcpy(data, stream.ConsumeBytes<char>(new_size).data(), new_size);
  }

  // If the new size is larger than the current size, fill the remaining space
  // with random bytes.
  if (new_size > size) {
    std::vector<char> random_bytes = stream.ConsumeBytes<char>(new_size - size);
    memcpy(data + size, random_bytes.data(), random_bytes.size());
  }

  // Return the new size of the input.
  return new_size;
}