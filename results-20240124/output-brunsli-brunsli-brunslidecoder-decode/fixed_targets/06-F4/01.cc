#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder decoder;
  size_t decoded_size;
  uint8_t* decoded_data;
  size_t output_size;
  decoder.Decode(&decoded_size, &data, &decoded_data, &output_size);
  return 0;
}