 #include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  brunsli::BrunsliDecoder decoder;
  size_t decoded_size = 0;
  char *decoded_data = nullptr;
  size_t output_size = 0;
  char *output_data = nullptr;
  int ret = decoder.Decode(&decoded_size, &decoded_data, &output_size,
                           &output_data);
  if (ret == brunsli::BRUNSLI_OK) {
    free(decoded_data);
    free(output_data);
  }
  return 0;
}