#include <brunsli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t len = fdp.ConsumeIntegralInRange<size_t>(0, 1 << 30);
  char *buf = new char[len];
  fdp.ConsumeBytes(buf, len);
  size_t res = brunsli::BrunsliEstimateDecoderPeakMemoryUsage(buf, len);
  delete[] buf;
  return res;
}