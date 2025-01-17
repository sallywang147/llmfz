 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t seq_size = provider.ConsumeIntegral<size_t>();
  std::vector<char> buffer(seq_size);
  size_t generated_size = ZSTD_generateSequences(nullptr, nullptr, seq_size,
                                                 buffer.data(), buffer.size());
  if (generated_size == (size_t)-1) {
    return 0;
  }
  return 0;
}