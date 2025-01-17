#include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  struct roaring_bitmap_s *r1 = roaring_bitmap_create();
  struct roaring_bitmap_s *r2 = roaring_bitmap_create();
  std::vector<uint32_t> v1 = fdp.ConsumeIntegralVector<uint32_t>(fdp.ConsumeIntegralInRange<size_t>(0, 10000));
  std::vector<uint32_t> v2 = fdp.ConsumeIntegralVector<uint32_t>(fdp.ConsumeIntegralInRange<size_t>(0, 10000));
  roaring_bitmap_add_many(r1, v1.size(), v1.data());
  roaring_bitmap_add_many(r2, v2.size(), v2.data());
  roaring_bitmap_lazy_xor_inplace(r1, r2);
  roaring_bitmap_free(r1);
  roaring_bitmap_free(r2);
  return 0;
}