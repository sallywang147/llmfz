 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t num_bitmaps = fdp.ConsumeIntegral<size_t>();
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    bitmaps.push_back(roaring_bitmap_create());
  }
  struct roaring_bitmap_s *result = roaring_bitmap_or_many(num_bitmaps, bitmaps.data());
  roaring_bitmap_free(result);
  for (auto bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }
  return 0;
}