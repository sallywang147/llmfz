#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize two roaring bitmaps
  roaring_bitmap_t* bm1 = roaring_bitmap_create();
  roaring_bitmap_t* bm2 = roaring_bitmap_create();

  // Add some random values to the bitmaps
  while (stream.remaining_bytes() > 0) {
    uint32_t value = stream.ConsumeIntegral<uint32_t>();
    roaring_bitmap_add(bm1, value);
    value = stream.ConsumeIntegral<uint32_t>();
    roaring_bitmap_add(bm2, value);
  }

  // Perform the lazy xor operation
  roaring_bitmap_lazy_xor_inplace(bm1, bm2);

  // Cleanup
  roaring_bitmap_free(bm1);
  roaring_bitmap_free(bm2);

  return 0;
}