#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <utility>

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size, size_t max_size,
                                         int seed) {
  FuzzedDataProvider stream(data, size);

  // Mutate the size of the input.
  size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);
  if (new_size != size) {
    data = static_cast<char*>(realloc(data, new_size));
    if (data == nullptr) {
      return 0;
    }
    memset(data + size, 0, new_size - size);
    size = new_size;
  }

  // Mutate the contents of the input.
  for (size_t i = 0; i < size; i++) {
    data[i] = stream.ConsumeIntegral<uint8_t>();
  }

  return size;
}