 #include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int matrix[8];
  for (int i = 0; i < 8; i++) {
    matrix[i] = stream.ConsumeIntegral<int>();
  }
  bool is_matrix_valid = stream.ConsumeBool();
  std::string bytes = stream.ConsumeRemainingBytesAsString();
  char *bytes_ptr = bytes.c_str();
  brunsli::FindBestMatrix(matrix, is_matrix_valid, bytes_ptr);
  return 0;
}