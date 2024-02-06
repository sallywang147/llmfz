#include <brunsli/decode.h>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t result = brunsli::BrunsliEstimateDecoderPeakMemoryUsage(
      const_cast<char*>(reinterpret_cast<const char*>(data)), size);
  return result;
}