 #include <fuzzer/FuzzedDataProvider.h>
#include <roaring/roaring.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  struct roaring_bitmap_s *r = roaring_bitmap_create();
  size_t offset = fdp.ConsumeIntegral<size_t>();
  roaring_bitmap_add_offset(r, offset);
  roaring_bitmap_free(r);
  return 0;
}