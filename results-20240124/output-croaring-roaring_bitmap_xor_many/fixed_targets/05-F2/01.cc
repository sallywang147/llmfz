#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "roaring/roaring.h"

extern "C" {
#include "roaring/roaring_bitmap.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  size_t num_bitmaps = fdp.ConsumeIntegral<size_t>();
  if (num_bitmaps == 0) {
    return 0;
  }

  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    size_t bitmap_size = fdp.ConsumeIntegral<size_t>();
    std::vector<uint32_t> bitmap_data = fdp.ConsumeFixedLengthVector<uint32_t>(bitmap_size);
    roaring_bitmap_t* bitmap = roaring_bitmap_create();
    for (uint32_t value : bitmap_data) {
      roaring_bitmap_add(bitmap, value);
    }
    bitmaps.push_back(bitmap);
  }

  roaring_bitmap_t* result = roaring_bitmap_xor_many(num_bitmaps, reinterpret_cast<const roaring_bitmap_t**>(bitmaps.data()));

  roaring_bitmap_free(result);
  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }

  return 0;
}