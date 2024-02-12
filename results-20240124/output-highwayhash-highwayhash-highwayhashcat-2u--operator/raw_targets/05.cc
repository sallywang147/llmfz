 #include "highwayhash/highwayhash.h"

using highwayhash::HighwayHashCat;
using highwayhash::StringView;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(uint64_t) * 2) {
    return 0;
  }

  const uint64_t *u64s = reinterpret_cast<const uint64_t*>(data);
  const uint64_t key = u64s[0];
  data += sizeof(uint64_t);
  size -= sizeof(uint64_t);

  const uint64_t num_fragments = u64s[1];
  data += sizeof(uint64_t);
  size -= sizeof(uint64_t);

  if (num_fragments > 100) {
    return 0;
  }

  StringView fragments[100];
  for (size_t i = 0; i < num_fragments; ++i) {
    if (size < sizeof(uint64_t)) {
      return 0;
    }
    const uint64_t fragment_size = u64s[i];
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    if (fragment_size > 10000) {
      return 0;
    }

    fragments[i] = StringView(reinterpret_cast<const char*>(data),
                               fragment_size);
    data += fragment_size;
    size -= fragment_size;
  }

  HighwayHashCat<2u>::operator()(nullptr, key, fragments, num_fragments, true);
  return 0;
}