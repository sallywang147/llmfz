#include <highwayhash/highwayhash_dynamic.h>

extern "C" {
#include <highwayhash/highwayhash_dynamic.h>
}

namespace highwayhash {

template <uint64_t kSeed>
void HighwayHashCat(bool key, StringView* fragments, size_t num_fragments,
                    bool hash) {
  HighwayHashCat<kSeed>()(key, fragments, num_fragments, hash);
}

}  // namespace highwayhash

extern "C" {

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  StringView fragments[2];
  fragments[0] = StringView(data, size);
  highwayhash::HighwayHashCat<0>(false, fragments, 1, true);
  return 0;
}

}  // extern "C"