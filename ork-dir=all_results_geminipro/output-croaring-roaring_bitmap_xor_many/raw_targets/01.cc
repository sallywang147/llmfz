#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "roaring/roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_bitmaps = stream.ConsumeIntegral<size_t>();
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    bitmaps.push_back(roaring_bitmap_create());
  }

  size_t num_values = stream.ConsumeIntegral<size_t>();
  for (size_t i = 0; i < num_values; i++) {
    const uint32_t value = stream.ConsumeIntegral<uint32_t>();
    for (auto& bitmap : bitmaps) {
      roaring_bitmap_add(bitmap, value);
    }
  }

  roaring_bitmap_t* result = roaring_bitmap_xor_many(num_bitmaps, bitmaps.data());
  roaring_bitmap_free(result);

  for (auto& bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }

  return 0;
}