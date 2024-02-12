#include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t count = provider.ConsumeIntegral<size_t>();
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < count; i++) {
    size_t bitmap_size = provider.ConsumeIntegral<size_t>();
    std::vector<uint32_t> bitmap_data = provider.ConsumeBytes<uint32_t>(bitmap_size);
    roaring_bitmap_t* bitmap = roaring_bitmap_create();
    roaring_bitmap_add_many(bitmap, bitmap_data.size(), bitmap_data.data());
    bitmaps.push_back(bitmap);
  }
  roaring_bitmap_t** bitmaps_ptr = bitmaps.data();
  roaring_bitmap_t* result = roaring_bitmap_or_many(count, bitmaps_ptr);
  roaring_bitmap_free(result);
  for (size_t i = 0; i < count; i++) {
    roaring_bitmap_free(bitmaps[i]);
  }
  return 0;
}