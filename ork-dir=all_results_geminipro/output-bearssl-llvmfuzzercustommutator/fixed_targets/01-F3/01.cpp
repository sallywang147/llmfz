#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <libfuzzer/libfuzzer_mutator.h>
}

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size, size_t max_size,
                                         int seed) {
  FuzzedDataProvider stream(data, size);
  const size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);
  if (new_size == size) {
    return 0;
  }
  std::vector<uint8_t> new_data = stream.ConsumeBytes<uint8_t>(new_size);
  memcpy(data, new_data.data(), new_size);
  return new_size;
}