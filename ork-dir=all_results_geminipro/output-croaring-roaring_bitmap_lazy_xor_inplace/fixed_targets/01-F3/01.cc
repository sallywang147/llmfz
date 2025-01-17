#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "roaring/roaring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t bitmap_size = stream.ConsumeIntegral<uint8_t>();
  roaring_bitmap_t* bitmap1 = roaring_bitmap_create();
  roaring_bitmap_t* bitmap2 = roaring_bitmap_create();
  for (uint8_t i = 0; i < bitmap_size; i++) {
    const uint32_t value = stream.ConsumeIntegral<uint32_t>();
    if (stream.ConsumeBool()) {
      roaring_bitmap_add(bitmap1, value);
    }
    if (stream.ConsumeBool()) {
      roaring_bitmap_add(bitmap2, value);
    }
  }
  roaring_bitmap_lazy_xor_inplace(bitmap1, bitmap2);
  roaring_bitmap_free(bitmap1);
  roaring_bitmap_free(bitmap2);
  return 0;
}