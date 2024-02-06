#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size,
                                           size_t max_size, int seed) {
  FuzzedDataProvider stream(data, size);
  const size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);
  if (new_size == 0) {
    return 0;
  }
  char* new_data = reinterpret_cast<char*>(malloc(new_size));
  stream.ConsumeBytes<char>(new_data, new_size);
  free(data);
  return new_size;
}