 #include "roaring/roaring.h"

#include "fuzzer/FuzzedDataProvider.h"

#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  uint32_t num_bitmaps = fdp.ConsumeIntegral<uint32_t>();
  if (num_bitmaps > 10000) {
    return 0;
  }
  std::vector<roaring_bitmap_t *> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    uint32_t num_values = fdp.ConsumeIntegral<uint32_t>();
    if (num_values > 10000) {
      return 0;
    }
    std::vector<uint32_t> values;
    for (size_t j = 0; j < num_values; j++) {
      values.push_back(fdp.ConsumeIntegral<uint32_t>());
    }
    roaring_bitmap_t *bitmap = roaring_bitmap_create();
    for (size_t j = 0; j < num_values; j++) {
      roaring_bitmap_add(bitmap, values[j]);
    }
    bitmaps.push_back(bitmap);
  }
  roaring_bitmap_t *result = roaring_bitmap_xor_many(num_bitmaps, bitmaps.data());
  roaring_bitmap_free(result);
  for (size_t i = 0; i < num_bitmaps; i++) {
    roaring_bitmap_free(bitmaps[i]);
  }
  return 0;
}