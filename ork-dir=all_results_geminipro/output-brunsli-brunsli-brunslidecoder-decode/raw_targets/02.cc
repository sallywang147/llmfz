#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  size_t output_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  size_t actual_output_size = 0;
  char* output_data = nullptr;
  char* unused_output_data = nullptr;
  brunsli::BrunsliDecoder decoder;
  int result = decoder.Decode(nullptr, &input_size,
                             reinterpret_cast<char**>(&data), &output_size,
                             &output_data);
  if (result != 0) return 0;
  result = decoder.Decode(nullptr, &actual_output_size,
                             reinterpret_cast<char**>(&unused_output_data), &output_size,
                             &output_data);
  return 0;
}