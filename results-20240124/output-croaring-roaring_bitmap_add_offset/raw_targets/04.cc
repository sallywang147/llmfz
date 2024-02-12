 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  roaring_bitmap_t *bitmap = roaring_bitmap_create();
  while (fdp.remaining_bytes() > 0) {
    size_t offset = fdp.ConsumeIntegral<size_t>();
    roaring_bitmap_add_offset(bitmap, offset);
  }
  roaring_bitmap_free(bitmap);
  return 0;
}