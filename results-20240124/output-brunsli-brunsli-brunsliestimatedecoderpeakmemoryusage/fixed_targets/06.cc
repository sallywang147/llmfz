#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_size = stream.ConsumeIntegralInRange<size_t>(1, 1 << 20);
  std::vector<uint8_t> data_vec = stream.ConsumeBytes<uint8_t>(max_size);
  (void) brunsli::BrunsliEstimateDecoderPeakMemoryUsage(data_vec.data(), max_size);
  return 0;
}