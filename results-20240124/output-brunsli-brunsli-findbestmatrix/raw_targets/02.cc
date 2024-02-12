 #include <brunsli/brunsli_decode.h>
#include <brunsli/types.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int matrix[16];
  bool use_fast_path = stream.ConsumeBool();
  char* scratch = new char[1024];
  brunsli::FindBestMatrix(matrix, use_fast_path, scratch);
  delete[] scratch;
  return 0;
}