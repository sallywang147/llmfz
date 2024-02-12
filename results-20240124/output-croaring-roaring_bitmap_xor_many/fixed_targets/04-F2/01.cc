#include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"
#include <vector>

extern "C" {
#include "roaring/roaring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  const size_t num_bitmaps = fdp.ConsumeIntegralInRange<size_t>(1, 100);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    const size_t num_values = fdp.ConsumeIntegralInRange<size_t>(1, 100);
    std::vector<uint32_t> values;
    for (size_t j = 0; j < num_values; j++) {
      values.push_back(fdp.ConsumeIntegralInRange<uint32_t>(0, 1000000));
    }
    bitmaps.push_back(roaring_bitmap_create());
    for (uint32_t value : values) {
      roaring_bitmap_add(bitmaps.back(), value);
    }
  }
  roaring_bitmap_t* result = roaring_bitmap_xor_many(num_bitmaps, reinterpret_cast<const roaring_bitmap_t**>(bitmaps.data()));
  roaring_bitmap_free(result);
  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }
  return 0;
}