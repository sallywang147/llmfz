 #include <brunsli/types.h>
#include <brunsli/brunsli_decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliEstimateDecoderPeakMemoryUsage((char *)data, size);
  return 0;
}