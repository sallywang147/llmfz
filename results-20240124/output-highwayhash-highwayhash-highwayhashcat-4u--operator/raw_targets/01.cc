 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "highwayhash/highwayhash.h"
#include "highwayhash/highwayhash_target.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(uint64_t) * 4) {
    return 0;
  }

  // Generate the key.
  const uint64_t *u64s = reinterpret_cast<const uint64_t*>(data);
  highwayhash::HHKey key = {u64s[0], u64s[1], u64s[2], u64s[3]};
  data += sizeof(uint64_t) * 4;
  size -= sizeof(uint64_t) * 4;

  // Generate the fragments.
  FuzzedDataProvider provider(data, size);
  std::vector<highwayhash::StringView> fragments;
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0, provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<char>(next_size);
    fragments.emplace_back(next_input.data(), next_input.size());
  }

  // Compute the hash.
  highwayhash::HighwayHashCat<4u> hasher;
  size_t hash;
  hasher(nullptr, key, fragments.data(), fragments.size(), &hash);

  return 0;
}