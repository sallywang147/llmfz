#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <phmap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the allocator
  std::allocator<std::pair<const std::string, std::string>> allocator;

  // Initialize the HashtablezInfoHandle
  phmap::priv::HashtablezInfoHandle handle;

  // Allocate a block of memory
  size_t n = stream.ConsumeIntegralInRange<size_t>(1, 100);
  char* p = allocator.allocate(n);

  // Deallocate the memory block
  phmap::priv::Deallocate<8, decltype(allocator)>(&handle, p, n);

  return 0;
}