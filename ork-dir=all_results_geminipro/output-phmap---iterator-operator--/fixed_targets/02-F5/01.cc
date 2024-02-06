#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "phmap.h"
}

using namespace phmap;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto set = provider.ConsumeRemainingBytesAs<std::vector<std::pair<std::string, std::string>>>();
  raw_hash_set<FlatHashMapPolicy<std::string, std::string>, Hash<std::string>, EqualTo<std::string>,
                std::allocator<std::pair<const std::string, std::string>>>
      hash_set(set.begin(), set.end());
  auto it = hash_set.begin();
  ++it;
  return 0;
}