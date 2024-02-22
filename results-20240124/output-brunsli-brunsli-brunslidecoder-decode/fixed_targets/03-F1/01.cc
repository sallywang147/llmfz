#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  FuzzedDataProvider stream(data, size);
  size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  size_t output_size;
  char* output_data;
  int ret = decoder.Decode(data, input_size, &output_data, &output_size);
  free(output_data);
  return ret;
}