 #include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t max_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 30);
  size_t brunsli_estimate = brunsli::BrunsliEstimateDecoderPeakMemoryUsage(nullptr, max_size);
  return 0;
}