#include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t num_bitmaps = fdp.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    size_t bitmap_size = fdp.ConsumeIntegralInRange<size_t>(0, 1000);
    std::vector<uint32_t> bitmap_data = fdp.ConsumeIntegralVector<uint32_t>(bitmap_size, 0, 100000);
    roaring_bitmap_t* bitmap = roaring_bitmap_create();
    for (uint32_t value : bitmap_data) {
      roaring_bitmap_add(bitmap, value);
    }
    bitmaps.push_back(bitmap);
  }
  roaring_bitmap_t* result = roaring_bitmap_or_many(num_bitmaps, bitmaps.data());
  roaring_bitmap_free(result);
  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }
  return 0;
}