 #include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "roaring/roaring.h"

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<uint32_t> bitmap_data_a =
      fdp.ConsumeVecInRange<uint32_t>(500, 0, 1000);
  roaring_bitmap_t* a = roaring_bitmap_create();
  roaring_bitmap_add_many(a, bitmap_data_a.size(), bitmap_data_a.data());

  std::vector<uint32_t> bitmap_data_b =
      fdp.ConsumeVecInRange<uint32_t>(500, 0, 1000);
  roaring_bitmap_t* b = roaring_bitmap_create();
  roaring_bitmap_add_many(b, bitmap_data_b.size(), bitmap_data_b.data());

  bool lazy = fdp.ConsumeBool();
  roaring_bitmap_lazy_or(a, b, lazy);
  roaring_bitmap_free(a);
  roaring_bitmap_free(b);

  return 0;
}