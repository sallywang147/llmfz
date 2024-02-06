#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "roaring/roaring.h"

extern "C" {
#include "roaring/roaring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_bitmaps = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    const uint32_t bitmap_size = stream.ConsumeIntegralInRange<uint32_t>(0, 10000);
    std::vector<uint32_t> bitmap_values;
    for (size_t j = 0; j < bitmap_size; j++) {
      bitmap_values.push_back(stream.ConsumeIntegralInRange<uint32_t>(0, 1000000));
    }
    roaring_bitmap_t* bitmap = roaring_bitmap_create();
    for (const uint32_t value : bitmap_values) {
      roaring_bitmap_add(bitmap, value);
    }
    bitmaps.push_back(bitmap);
  }

  roaring_bitmap_t* result = roaring_bitmap_or_many(bitmaps.size(), bitmaps.data());
  roaring_bitmap_free(result);
  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }

  return 0;
}