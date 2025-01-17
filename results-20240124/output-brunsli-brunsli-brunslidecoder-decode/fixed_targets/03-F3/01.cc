#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  FuzzedDataProvider stream(data, size);
  size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  size_t output_size;
  char* output_data;
  const uint8_t* next_in = data;
  size_t available_out = size;
  int ret = decoder.Decode(&input_size, &next_in, &output_data, &output_size, &available_out);
  free(output_data);
  return ret;
}