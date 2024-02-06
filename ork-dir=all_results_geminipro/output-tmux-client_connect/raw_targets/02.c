#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t path_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> path_bytes = provider.ConsumeBytes<uint8_t>(path_size);
  char* path = reinterpret_cast<char*>(path_bytes.data());
  const size_t flags = provider.ConsumeIntegral<size_t>();
  client_connect(nullptr, path, flags);
  return 0;
}