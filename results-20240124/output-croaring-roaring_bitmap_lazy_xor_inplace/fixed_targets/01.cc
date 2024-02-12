 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  struct roaring_bitmap_s *r1 = roaring_bitmap_create();
  struct roaring_bitmap_s *r2 = roaring_bitmap_create();
  size_t n1 = fdp.ConsumeIntegralInRange<size_t>(0, 10000);
  for (size_t i = 0; i < n1; i++) {
    roaring_bitmap_add(r1, fdp.ConsumeIntegralInRange<uint32_t>(0, 1000000));
  }
  size_t n2 = fdp.ConsumeIntegralInRange<size_t>(0, 10000);
  for (size_t i = 0; i < n2; i++) {
    roaring_bitmap_add(r2, fdp.ConsumeIntegralInRange<uint32_t>(0, 1000000));
  }
  roaring_bitmap_lazy_xor_inplace(r1, r2);
  roaring_bitmap_free(r1);
  roaring_bitmap_free(r2);
  return 0;
}