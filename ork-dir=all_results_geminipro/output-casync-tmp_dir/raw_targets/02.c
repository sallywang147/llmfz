#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t max_path_length = provider.ConsumeIntegralInRange<size_t>(
      0, 1 << 16);
  std::vector<char> path(max_path_length);
  provider.ConsumeBytes(path.data(), path.size());
  char* ret = nullptr;
  int result = tmp_dir(&ret);
  free(ret);
  return result;
}