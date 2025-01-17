#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t size_to_allocate = provider.ConsumeIntegralInRange<size_t>(0, 100000);
  std::vector<uint8_t> data_to_allocate(size_to_allocate);
  provider.ConsumeBytes<uint8_t>(&data_to_allocate[0], size_to_allocate);

  void* ptr = malloc(size_to_allocate);
  if (ptr == nullptr) {
    return 0;
  }

  // Call the target function
  unpack_pack_fuzzer_cpp(ptr, size_to_allocate);

  free(ptr);

  return 0;
}

// The target function definition
extern "C" void unpack_pack_fuzzer_cpp(void* data, size_t size) {
  // Implement the target function here
}