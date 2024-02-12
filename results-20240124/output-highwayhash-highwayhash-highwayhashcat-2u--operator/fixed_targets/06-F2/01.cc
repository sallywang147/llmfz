#include "highwayhash/highwayhash_target.h"
#include "highwayhash/highwayhash_types.h"
#include "highwayhash/string_view.h"

using highwayhash::HHKey;
using highwayhash::HHResult64;
using highwayhash::HighwayHash;
using highwayhash::HighwayHashCat;
using highwayhash::StringView;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(uint64_t) * 4) {
    return 0;
  }

  // Generate the key.
  const uint64_t *u64s = reinterpret_cast<const uint64_t*>(data);
  HH_ALIGNAS(32) const HHKey key = {u64s[0], u64s[1], u64s[2], u64s[3]};
  data += sizeof(uint64_t) * 4;
  size -= sizeof(uint64_t) * 4;

  // Generate the fragments.
  std::vector<StringView> fragments;
  while (size > 0) {
    const size_t fragment_size = std::min(size, 1024 * 1024);
    fragments.emplace_back(reinterpret_cast<const char*>(data), fragment_size);
    data += fragment_size;
    size -= fragment_size;
  }

  // Compute the hash.
  HHResult64 result;
  HighwayHashCat<2u>()(nullptr, key, fragments.data(), fragments.size(), false, &result);
  return 0;
}