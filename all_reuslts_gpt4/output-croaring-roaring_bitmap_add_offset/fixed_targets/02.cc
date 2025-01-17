#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new bitmap
  roaring_bitmap_t *bitmap = roaring_bitmap_create();
  if (!bitmap) {
    return 0;
  }

  // Add some values to the bitmap
  while (stream.remaining_bytes() > 0) {
    uint32_t value = stream.ConsumeIntegral<uint32_t>();
    roaring_bitmap_add(bitmap, value);
  }

  // Get a random offset
  size_t offset = stream.ConsumeIntegral<size_t>();

  // Call the target function
  roaring_bitmap_t *result = roaring_bitmap_add_offset(bitmap, offset);

  // Clean up
  roaring_bitmap_free(result);
  roaring_bitmap_free(bitmap);

  return 0;
}