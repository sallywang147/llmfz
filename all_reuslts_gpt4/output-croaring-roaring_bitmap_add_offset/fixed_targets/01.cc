#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <roaring/roaring.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new bitmap
  roaring_bitmap_t* bitmap = roaring_bitmap_create();
  if (bitmap == nullptr) {
    return 0;
  }

  // Consume data to add to the bitmap
  while (stream.remaining_bytes() > 0) {
    uint32_t value = stream.ConsumeIntegral<uint32_t>();
    roaring_bitmap_add(bitmap, value);
  }

  // Consume data to use as offset
  size_t offset = stream.ConsumeIntegral<size_t>();

  // Call the target function
  struct roaring_bitmap_s * new_bitmap = roaring_bitmap_add_offset(bitmap, offset);

  // Cleanup
  roaring_bitmap_free(bitmap);
  roaring_bitmap_free(new_bitmap);

  return 0;
}