#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <roaring/roaring.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t num_bitmaps = stream.ConsumeIntegralInRange<size_t>(1, 100);
  struct roaring_bitmap_s **bitmaps = (struct roaring_bitmap_s **)malloc(num_bitmaps * sizeof(struct roaring_bitmap_s *));
  
  for (size_t i = 0; i < num_bitmaps; i++) {
    size_t bitmap_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
    bitmaps[i] = roaring_bitmap_create_with_capacity(bitmap_size);
    for (size_t j = 0; j < bitmap_size; j++) {
      uint32_t value = stream.ConsumeIntegral<uint32_t>();
      roaring_bitmap_add(bitmaps[i], value);
    }
  }

  struct roaring_bitmap_s *result_bitmap = roaring_bitmap_xor_many(num_bitmaps, bitmaps);

  for (size_t i = 0; i < num_bitmaps; i++) {
    roaring_bitmap_free(bitmaps[i]);
  }
  free(bitmaps);
  roaring_bitmap_free(result_bitmap);
  
  return 0;
}