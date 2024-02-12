 #include <roaring/roaring.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  roaring_bitmap_t *bitmap_a = roaring_bitmap_create();
  roaring_bitmap_t *bitmap_b = roaring_bitmap_create();

  std::vector<uint32_t> bitmap_data_a =
      roaring::roaring_bitmap_consume_vec_in_range(fdp, 500, 0, 1000);
  roaring_bitmap_add_many(bitmap_a, bitmap_data_a.size(), bitmap_data_a.data());
  roaring_bitmap_run_optimize(bitmap_a);
  roaring_bitmap_shrink_to_fit(bitmap_a);

  std::vector<uint32_t> bitmap_data_b =
      roaring::roaring_bitmap_consume_vec_in_range(fdp, 500, 0, 1000);
  roaring_bitmap_add_many(bitmap_b, bitmap_data_b.size(), bitmap_data_b.data());
  roaring_bitmap_run_optimize(bitmap_b);
  roaring_bitmap_shrink_to_fit(bitmap_b);

  roaring_bitmap_lazy_or(bitmap_a, bitmap_b, fdp.ConsumeBool());

  roaring_bitmap_free(bitmap_a);
  roaring_bitmap_free(bitmap_b);

  return 0;
}

namespace roaring {

std::vector<uint32_t> roaring_bitmap_consume_vec_in_range(FuzzedDataProvider &fdp,
                                                        size_t length,
                                                        uint32_t min_value,
                                                        uint32_t max_value) {
  std::vector<uint32_t> result = {0};
  result.resize(length);
  std::generate(result.begin(), result.end(), [&]() {
    return fdp.ConsumeIntegralInRange<uint32_t>(min_value, max_value);
  });
  return result;
}

} // namespace roaring