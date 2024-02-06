#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size, size_t max_size,
                                         int seed) {
  FuzzedDataProvider stream(data, size);
  const size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);
  std::vector<uint8_t> new_data = stream.ConsumeBytes<uint8_t>(new_size);
  memcpy(data, new_data.data(), new_size);
  return new_size;
}
```

The fix adds the necessary `#include <vector>` directive to include the header for the `std::vector` class. This allows the code to compile and run without the undefined reference error.