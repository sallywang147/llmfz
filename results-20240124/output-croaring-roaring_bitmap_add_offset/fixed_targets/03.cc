 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  struct roaring_bitmap_s *bitmap = roaring_bitmap_create();
  size_t offset = fdp.ConsumeIntegral<size_t>();
  roaring_bitmap_add_offset(bitmap, offset);
  roaring_bitmap_free(bitmap);
  return 0;
}