#include <brunsli/decode.h>

extern "C" {
#include <stddef.h>
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t result = brunsli::BrunsliEstimateDecoderPeakMemoryUsage(
      reinterpret_cast<const char*>(data), size);
  return result;
}
```

The original code has no issues. Therefore, no changes are needed.