 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  roaring_bitmap_t* bm = roaring_bitmap_create();
  size_t offset = fdp.ConsumeIntegral<size_t>();
  roaring_bitmap_add_offset(bm, offset);
  roaring_bitmap_free(bm);
  return 0;
}