#include <brunsli/decode.h>
#include <vector>

extern "C" {
#include <stddef.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<int> matrix(16);
  brunsli::FindBestMatrix(matrix.data(), false, nullptr);
  return 0;
}
}