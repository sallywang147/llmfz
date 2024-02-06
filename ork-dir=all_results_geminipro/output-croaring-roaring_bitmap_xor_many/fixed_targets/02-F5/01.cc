#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "roaring/roaring.h"
}

extern "C" roaring_bitmap_t* roaring_bitmap_xor_many(size_t, roaring_bitmap_t**);
extern "C" void roaring_bitmap_free(roaring_bitmap_t*);
extern "C" void roaring_bitmap_add(roaring_bitmap_t*, uint32_t);
extern "C" roaring_bitmap_t* roaring_bitmap_create();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t bitmap_count = stream.ConsumeIntegral<size_t>();
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < bitmap_count; ++i) {
    const size_t bitmap_size = stream.ConsumeIntegral<size_t>();
    std::vector<uint32_t> bitmap_data(bitmap_size);
    stream.ConsumeIntegralVector<uint32_t>(&bitmap_data, bitmap_size);
    bitmaps.push_back(roaring_bitmap_create());
    for (auto value : bitmap_data) {
      roaring_bitmap_add(bitmaps.back(), value);
    }
  }

  roaring_bitmap_t* result = roaring_bitmap_xor_many(bitmap_count, bitmaps.data());
  roaring_bitmap_free(result);
  for (auto bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }
  return 0;
}