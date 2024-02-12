#include <brunsli/decode.h>
#include <brunsli/brunsli_decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int num_matrices = stream.ConsumeIntegralInRange<int>(0, 10);
  bool is_chroma_diff = stream.ConsumeBool();
  std::string matrix_data = stream.ConsumeBytesAsString(size);
  int result = brunsli::FindBestMatrix(&num_matrices, is_chroma_diff, matrix_data.c_str());
  return result;
}