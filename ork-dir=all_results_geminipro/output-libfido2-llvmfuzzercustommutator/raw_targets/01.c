#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size, size_t max_size,
                                          int seed) {
  FuzzedDataProvider stream(data, size);
  const size_t new_size =
      stream.ConsumeIntegralInRange<size_t>(0, std::min(max_size, size));
  const std::string new_data = stream.ConsumeRemainingBytesAsString();
  if (new_data.size() != new_size) {
    return 0;
  }
  memcpy(data, new_data.c_str(), new_size);
  return new_size;
}