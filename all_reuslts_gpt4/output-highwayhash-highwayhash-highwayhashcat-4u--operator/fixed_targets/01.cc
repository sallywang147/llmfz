#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "highwayhash/highwayhash_cat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize HighwayHashCat
  highwayhash::HighwayHashCat<4u> hash_cat;

  // Extract key
  bool key = stream.ConsumeBool();

  // Extract number of fragments
  size_t num_fragments = stream.ConsumeIntegralInRange<size_t>(0, 10);

  // Extract fragments
  std::vector<highwayhash::StringView> fragments;
  for (size_t i = 0; i < num_fragments; ++i) {
    std::string fragment = stream.ConsumeRandomLengthString();
    fragments.push_back(highwayhash::StringView(fragment));
  }

  // Initialize hash
  size_t hash[4] = {0};

  // Call operator
  hash_cat(std::integral_constant<bool, key>(), fragments.data(), fragments.size(), hash);

  return 0;
}