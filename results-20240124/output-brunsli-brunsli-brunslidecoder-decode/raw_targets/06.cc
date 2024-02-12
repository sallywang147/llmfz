 #include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder decoder;
  size_t decoded_size;
  char* decoded_data;
  size_t output_size;
  char* output_data;
  decoder.Decode(nullptr, &decoded_size, &decoded_data, &output_size,
                 &output_data);
  return 0;
}