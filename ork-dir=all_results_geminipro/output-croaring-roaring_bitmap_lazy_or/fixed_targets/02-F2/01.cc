#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "roaring.h"

extern "C" roaring_bitmap_t* roaring_bitmap_lazy_or(roaring_bitmap_t* bitmap1, roaring_bitmap_t* bitmap2, int inplace);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t bitmap_count = stream.ConsumeIntegralInRange<uint8_t>(1, 10);
  std::vector<roaring_bitmap_t*> bitmaps;
  for (uint8_t i = 0; i < bitmap_count; ++i) {
    const uint32_t bitmap_size = stream.ConsumeIntegralInRange<uint32_t>(0, 10000);
    auto bitmap_data = stream.ConsumeBytes<uint8_t>(bitmap_size);
    bitmaps.push_back(roaring_bitmap_from_bytes(bitmap_data.data(), bitmap_size));
  }

  const bool inplace = stream.ConsumeBool();
  roaring_bitmap_t* result = inplace ? bitmaps[0] : roaring_bitmap_lazy_or(bitmaps[0], bitmaps[1], inplace);
  roaring_bitmap_free(result);

  for (roaring_bitmap_t* bitmap : bitmaps) {
    roaring_bitmap_free(bitmap);
  }

  return 0;
}