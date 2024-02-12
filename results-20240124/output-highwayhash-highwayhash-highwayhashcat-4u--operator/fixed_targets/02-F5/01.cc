#include <highwayhash/highwayhash_target.h>
#include <highwayhash/highwayhash_types.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t HighwayHashCat4(const char* bytes, size_t size) {
  return highwayhash::HighwayHashCat<4u>()(bytes, size);
}

#ifdef __cplusplus
}
#endif