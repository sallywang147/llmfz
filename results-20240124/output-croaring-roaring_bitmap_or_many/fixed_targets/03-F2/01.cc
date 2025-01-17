#include "fuzzer/FuzzedDataProvider.h"
#include <vector>
#include <roaring/roaring.h>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t count = fdp.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < count; i++) {
    size_t bitmap_size = fdp.ConsumeIntegralInRange<size_t>(0, 1000);
    std::vector<uint32_t> bitmap_data = fdp.ConsumeFixedLengthData<uint32_t>(bitmap_size);
    bitmaps.push_back(roaring_bitmap_create());
    for (uint32_t value : bitmap_data) {
      roaring_bitmap_add(bitmaps.back(), value);
    }
  }
  roaring_bitmap_t* result = roaring_bitmap_or_many(count, reinterpret_cast<const roaring_bitmap_t**>(bitmaps.data()));
  roaring_bitmap_free(result);
  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }
  return 0;
}
}