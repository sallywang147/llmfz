 #include "highwayhash/highwayhash_target.h"
#include "highwayhash/highwayhash_types.h"

using highwayhash::HHKey;
using highwayhash::HHResult64;
using highwayhash::HighwayHash;
using highwayhash::HighwayHashCat;
using highwayhash::StringView;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(uint64_t) * 4) {
    return 0;
  }

  // Generate the key.
  const uint64_t *u64s = reinterpret_cast<const uint64_t*>(data);
  HH_ALIGNAS(32) const HHKey key = {u64s[0], u64s[1], u64s[2], u64s[3]};
  data += sizeof(uint64_t) * 4;
  size -= sizeof(uint64_t) * 4;

  // Generate the fragments.
  const size_t num_fragments = size / 2;
  StringView fragments[num_fragments];
  for (size_t i = 0; i < num_fragments; ++i) {
    fragments[i] = StringView(reinterpret_cast<const char*>(data), size / 2);
    data += size / 2;
    size -= size / 2;
  }

  // Compute the hash.
  HHResult64 result;
  HighwayHashCat<2u>()(key, fragments, num_fragments, true);
  return 0;
}