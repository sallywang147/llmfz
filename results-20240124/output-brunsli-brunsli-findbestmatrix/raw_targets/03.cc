 #include <brunsli/brunsli_decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  int matrix[64];
  brunsli::FindBestMatrix(matrix, false, nullptr);
  return 0;
}