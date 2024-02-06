#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare the parameters for LLVMFuzzerCustomMutator
  size_t max_size = stream.ConsumeIntegral<size_t>();
  int seed = stream.ConsumeIntegral<int>();

  // Prepare the buffer for LLVMFuzzerCustomMutator
  std::vector<char> buffer(size);
  for (size_t i = 0; i < size; ++i) {
    buffer[i] = stream.ConsumeIntegral<char>();
  }

  // Call LLVMFuzzerCustomMutator
  size_t new_size = LLVMFuzzerCustomMutator(buffer.data(), size, max_size, seed);

  return 0;
}