 #include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t max_input_size = stream.ConsumeIntegral<size_t>();
  brunsli::BrunsliEstimateDecoderPeakMemoryUsage(nullptr, max_input_size);
  return 0;
}