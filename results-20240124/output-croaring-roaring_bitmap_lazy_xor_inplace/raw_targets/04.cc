 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  roaring_bitmap_t *bitmap_a = roaring_bitmap_create();
  roaring_bitmap_t *bitmap_b = roaring_bitmap_create();

  std::vector<uint32_t> bitmap_data_a = fdp.ConsumeVec<uint32_t>(1000);
  roaring_bitmap_add_many(bitmap_a, bitmap_data_a.size(), bitmap_data_a.data());

  std::vector<uint32_t> bitmap_data_b = fdp.ConsumeVec<uint32_t>(1000);
  roaring_bitmap_add_many(bitmap_b, bitmap_data_b.size(), bitmap_data_b.data());

  roaring_bitmap_lazy_xor_inplace(bitmap_a, bitmap_b);

  roaring_bitmap_free(bitmap_a);
  roaring_bitmap_free(bitmap_b);

  return 0;
}