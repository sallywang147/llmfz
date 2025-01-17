#include "fuzzer/FuzzedDataProvider.h"
#include "roaring/roaring.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "roaring/roaring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t count = fdp.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<roaring_bitmap_t *> bitmaps;
  for (size_t i = 0; i < count; i++) {
    const size_t bitmap_size = fdp.ConsumeIntegralInRange<size_t>(0, 100);
    const uint32_t *bitmap_data = fdp.ConsumeIntegralArray<uint32_t>(bitmap_size);
    bitmaps.push_back(roaring_bitmap_create_from_data(bitmap_size, bitmap_data));
  }
  roaring_bitmap_t *result = roaring_bitmap_xor_many(count, reinterpret_cast<const roaring_bitmap_t **>(bitmaps.data()));
  roaring_bitmap_free(result);
  for (size_t i = 0; i < count; i++) {
    roaring_bitmap_free(bitmaps[i]);
  }
  return 0;
}