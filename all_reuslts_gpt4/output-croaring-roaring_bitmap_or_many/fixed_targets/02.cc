#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t bitmap_count = provider.ConsumeIntegralInRange<size_t>(0, 10);
  struct roaring_bitmap_s **bitmaps = new struct roaring_bitmap_s *[bitmap_count];

  for (size_t i = 0; i < bitmap_count; ++i) {
    bitmaps[i] = roaring_bitmap_create();
    size_t num_values = provider.ConsumeIntegralInRange<size_t>(0, 100);
    for (size_t j = 0; j < num_values; ++j) {
      uint32_t value = provider.ConsumeIntegral<uint32_t>();
      roaring_bitmap_add(bitmaps[i], value);
    }
  }

  struct roaring_bitmap_s *result_bitmap = roaring_bitmap_or_many(bitmap_count, bitmaps);

  // Cleanup
  for (size_t i = 0; i < bitmap_count; ++i) {
    roaring_bitmap_free(bitmaps[i]);
  }
  roaring_bitmap_free(result_bitmap);
  delete[] bitmaps;

  return 0;
}