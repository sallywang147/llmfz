#include "fuzzer/FuzzedDataProvider.h"
#include <cstddef>
#include <cstdint>
#include <vector>
#include "roaring/roaring.h"

extern "C" {
#include "roaring/roaring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t num_bitmaps = fdp.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    bitmaps.push_back(roaring_bitmap_create());
  }
  for (size_t i = 0; i < num_bitmaps; i++) {
    size_t num_values = fdp.ConsumeIntegralInRange<size_t>(0, 10000);
    for (size_t j = 0; j < num_values; j++) {
      uint32_t value = fdp.ConsumeIntegralInRange<uint32_t>(0, 1000000);
      roaring_bitmap_add(bitmaps[i], value);
    }
  }
  roaring_bitmap_t* result = roaring_bitmap_xor_many(num_bitmaps, (const roaring_bitmap_t**)bitmaps.data());
  roaring_bitmap_free(result);
  for (size_t i = 0; i < num_bitmaps; i++) {
    roaring_bitmap_free(bitmaps[i]);
  }
  return 0;
}