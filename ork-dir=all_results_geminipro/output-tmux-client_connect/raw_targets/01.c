#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t flags = provider.ConsumeIntegral<size_t>();
  std::string path = provider.ConsumeRandomLengthString();
  client_connect(nullptr, path.c_str(), flags);
  return 0;
}