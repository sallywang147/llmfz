#include "highwayhash/highwayhash_target.h"
#include "highwayhash/highwayhash_types.h"
#include "highwayhash/highwayhash_cat.h" // Include this header file

using highwayhash::HHKey;
using highwayhash::HHResult64;
using highwayhash::HighwayHash;
using highwayhash::HighwayHashCat;
using highwayhash::StringView;

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Generate the key.
  const uint64_t key = *reinterpret_cast<const uint64_t*>(data);
  data += sizeof(uint64_t);
  size -= sizeof(uint64_t);

  // Generate the fragments.
  std::vector<StringView> fragments;
  while (size >= sizeof(uint64_t)) {
    const uint64_t fragment_size = *reinterpret_cast<const uint64_t*>(data);
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);
    if (fragment_size > size) {
      break;
    }
    fragments.emplace_back(reinterpret_cast<const char*>(data), fragment_size);
    data += fragment_size;
    size -= fragment_size;
  }

  // Compute the hash.
  HHResult64 result;
  HighwayHashCat<4u>::operator()(nullptr, key, fragments.data(), fragments.size(),
                                &result);
  return 0;
}
}