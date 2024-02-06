#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create two bitmaps
  roaring_bitmap_t *rb1 = roaring_bitmap_create();
  roaring_bitmap_t *rb2 = roaring_bitmap_create();

  // Populate the bitmaps with random data
  while (stream.remaining_bytes() > 0) {
    uint32_t value = stream.ConsumeIntegral<uint32_t>();
    if (stream.ConsumeBool()) {
      roaring_bitmap_add(rb1, value);
    } else {
      roaring_bitmap_add(rb2, value);
    }
  }

  // Perform lazy OR operation
  bool high_cardinality = stream.ConsumeBool();
  roaring_bitmap_t *rb3 = roaring_bitmap_lazy_or(rb1, rb2, high_cardinality);

  // Cleanup
  roaring_bitmap_free(rb1);
  roaring_bitmap_free(rb2);
  roaring_bitmap_free(rb3);

  return 0;
}