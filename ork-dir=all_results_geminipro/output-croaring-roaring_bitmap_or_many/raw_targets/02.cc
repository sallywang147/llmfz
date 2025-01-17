#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_bitmaps = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (size_t i = 0; i < num_bitmaps; i++) {
    roaring_bitmap_t* bitmap = roaring_bitmap_create();
    const size_t num_values = stream.ConsumeIntegralInRange<size_t>(0, 1000);
    for (size_t j = 0; j < num_values; j++) {
      const uint64_t value = stream.ConsumeIntegral<uint64_t>();
      roaring_bitmap_add(bitmap, value);
    }
    bitmaps.push_back(bitmap);
  }

  roaring_bitmap_t* result = roaring_bitmap_or_many(num_bitmaps, bitmaps.data());
  roaring_bitmap_free(result);

  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }

  return 0;
}