 #include <brunsli/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliEstimateDecoderPeakMemoryUsage(const_cast<char*>(reinterpret_cast<const char*>(data)), size);
  return 0;
}