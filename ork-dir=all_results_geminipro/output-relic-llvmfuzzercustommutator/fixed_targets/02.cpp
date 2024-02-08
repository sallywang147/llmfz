#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <stdint.h>
}

extern "C" size_t LLVMFuzzerCustomMutator(char* data, size_t size, size_t max_size,
                                         int seed) {
  FuzzedDataProvider stream(data, size);
  const size_t new_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);
  std::vector<uint8_t> new_data = stream.ConsumeBytes<uint8_t>(new_size);
  memcpy(data, new_data.data(), new_size);
  return new_size;
}
```

The issue was that the `stdint.h` header was not included. This header is necessary for the definition of the `uint8_t` type. To fix the issue, the `stdint.h` header was included and wrapped with `extern "C" {}`.