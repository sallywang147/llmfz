#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  brunsli::BrunsliDecoder decoder;
  size_t available_in = size;
  const uint8_t* next_in = data;
  size_t out_size = 0;
  char* out_data = nullptr;
  size_t metadata_size = 0;
  char* metadata_data = nullptr;
  FuzzedDataProvider stream(data, size);

  decoder.Decode(&available_in, &next_in, &out_data,
                 &out_size, &metadata_data, &metadata_size);

  free(out_data);
  free(metadata_data);

  return 0;
}