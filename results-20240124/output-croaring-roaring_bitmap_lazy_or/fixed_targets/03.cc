 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  roaring_bitmap_t *a = roaring_bitmap_create();
  roaring_bitmap_t *b = roaring_bitmap_create();
  roaring_bitmap_lazy_or(a, b, fdp.ConsumeBool());
  roaring_bitmap_free(a);
  roaring_bitmap_free(b);
  return 0;
}