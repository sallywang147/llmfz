#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  size_t available_in = size;
  const uint8_t* next_in = data;
  size_t available_out = 0;
  uint8_t* next_out = nullptr;
  size_t out_size = 0;
  char* out_data = nullptr;
  FuzzedDataProvider stream(data, size);

  decoder.Decode(&available_in, &next_in, &available_out, &next_out, &out_data, &out_size);

  free(out_data);

  return 0;
}