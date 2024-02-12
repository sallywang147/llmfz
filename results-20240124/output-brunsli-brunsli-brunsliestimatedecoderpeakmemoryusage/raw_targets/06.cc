 #include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_size = stream.ConsumeIntegralInRange<size_t>(1, 1 << 20);
  char *data_ptr = new char[max_size];
  stream.ConsumeBytes<char>(data_ptr, max_size);
  (void) brunsli::BrunsliEstimateDecoderPeakMemoryUsage(data_ptr, max_size);
  delete[] data_ptr;
  return 0;
}