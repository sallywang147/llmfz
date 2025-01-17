#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "highwayhash/highwayhash.h"
#include "highwayhash/highwayhash_target.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  
  // Consume the first two bytes for the keys
  bool key1 = stream.ConsumeBool();
  bool key2 = stream.ConsumeBool();
  
  // Create a HighwayHashCat object
  highwayhash::HighwayHashCat<2> hashcat({key1, key2});
  
  // Consume the remaining data for the fragments
  std::vector<highwayhash::StringView> fragments;
  while (stream.remaining_bytes() > 0) {
    std::string fragment = stream.ConsumeRandomLengthString();
    fragments.push_back(highwayhash::StringView(fragment));
  }
  
  // Compute the hash
  bool hash;
  hashcat(std::integral_constant<bool, true>(), fragments.data(), fragments.size(), &hash);
  
  return 0;
}