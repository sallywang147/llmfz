#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  size_t max_size = provider.ConsumeIntegral<size_t>();
  int seed = provider.ConsumeIntegral<int>();

  std::vector<char> buf_vector = provider.ConsumeRemainingBytes<char>();
  char* buf = buf_vector.data();

  size_t new_size = LLVMFuzzerCustomMutator(buf, size, max_size, seed);

  return 0;
}