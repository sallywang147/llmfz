 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

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
  FuzzedDataProvider provider(data, size);
  const size_t num_fragments = provider.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<StringView> fragments(num_fragments);
  for (size_t i = 0; i < num_fragments; ++i) {
    const size_t fragment_size = provider.ConsumeIntegralInRange<size_t>(0, size);
    fragments[i] = StringView(reinterpret_cast<const char*>(data), fragment_size);
    data += fragment_size;
    size -= fragment_size;
  }

  // Compute the hash.
  HHResult64 result;
  HighwayHashCat<4u>::operator()(nullptr, key, fragments.data(), num_fragments,
                                 &result);
  return 0;
}