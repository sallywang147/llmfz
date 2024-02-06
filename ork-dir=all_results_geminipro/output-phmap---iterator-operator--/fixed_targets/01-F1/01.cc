#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "phmap.h"

using namespace phmap;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    phmap::priv::initialize();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  size_t num_entries = provider.ConsumeIntegralInRange<size_t>(0, 10000);
  phmap::priv::raw_hash_set<phmap::priv::FlatHashMapPolicy<std::string, std::string>, phmap::Hash<std::string>, phmap::EqualTo<std::string>, std::allocator<std::pair<const std::string, std::string>>>::iterator iter;
  phmap::priv::raw_hash_set<phmap::priv::FlatHashMapPolicy<std::string, std::string>, phmap::Hash<std::string>, phmap::EqualTo<std::string>, std::allocator<std::pair<const std::string, std::string>>> set;
  for (size_t i = 0; i < num_entries; i++) {
    auto key = provider.ConsumeRandomLengthString();
    auto value = provider.ConsumeRandomLengthString();
    set.insert(std::make_pair(key, value));
  }

  for (iter = set.begin(); iter != set.end(); ++iter) {
  }

  phmap::priv::destroy();

  return 0;
}