 #include <fuzzer/FuzzedDataProvider.h>
#include <roaring/roaring.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t num_bitmaps = fdp.ConsumeIntegralInRange<size_t>(0, 100);
  roaring_bitmap_t **bitmaps =
      (roaring_bitmap_t **)malloc(sizeof(roaring_bitmap_t *) * num_bitmaps);
  for (size_t i = 0; i < num_bitmaps; i++) {
    bitmaps[i] = roaring_bitmap_create();
    roaring_bitmap_add(bitmaps[i], fdp.ConsumeIntegral<uint32_t>());
  }
  roaring_bitmap_or_many(num_bitmaps, bitmaps);
  for (size_t i = 0; i < num_bitmaps; i++) {
    roaring_bitmap_free(bitmaps[i]);
  }
  free(bitmaps);
  return 0;
}