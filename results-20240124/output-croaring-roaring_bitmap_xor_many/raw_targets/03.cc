 #include "roaring/roaring.h"
#include "fuzzer/FuzzedDataProvider.h"
#include <vector>

std::vector<uint32_t> ConsumeVecInRange(FuzzedDataProvider &fdp, size_t length,
                                        uint32_t min_value,
                                        uint32_t max_value) {
  std::vector<uint32_t> result = {0};
  result.resize(length);
  std::generate(result.begin(), result.end(), [&]() {
    return fdp.ConsumeIntegralInRange<uint32_t>(min_value, max_value);
  });
  return result;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  /**
   * A bitmap may contain up to 2**32 elements. Later this function will
   * output the content to an array where each element uses 32 bits of storage.
   * That would use 16 GB. Thus this function is bound to run out of memory.
   *
   * Even without the full serialization to a 32-bit array, a bitmap may still use over
   * 512 MB in the normal course of operation: that is to be expected since it can
   * represent all sets of integers in [0,2**32]. This function may hold several
   * bitmaps in memory at once, so it can require gigabytes of memory (without bugs).
   * Hence, unless it has a generous memory capacity, this function will run out of memory
   * almost certainly.
   *
   * For sanity, we may limit the range to, say, 10,000,000 which will use 38 MB or so.
   * With such a limited range, if we run out of memory, then we can almost certain that it
   * has to do with a genuine bug.
   */

  uint32_t range_start = 0;
  uint32_t range_end = 10'000'000;

  /**
   * We are not solely dependent on the range [range_start, range_end) because
   * ConsumeVecInRange below produce integers in a small range starting at 0.
   */

  FuzzedDataProvider fdp(data, size);
  /**
   * The next line was ConsumeVecInRange(fdp, 500, 0, 1000) but it would pick 500
   * values at random from 0, 1000, making almost certain that all of the values are
   * picked. It seems more useful to pick 500 values in the range 0,1000.
   */
  std::vector<uint32_t> bitmap_data_a = ConsumeVecInRange(fdp, 500, 0, 1000);
  roaring_bitmap_t *a = roaring_bitmap_create();
  for (uint32_t i = 0; i < bitmap_data_a.size(); i++) {
    roaring_bitmap_add(a, bitmap_data_a[i]);
  }

  std::vector<uint32_t> bitmap_data_b = ConsumeVecInRange(fdp, 500, 0, 1000);
  roaring_bitmap_t *b = roaring_bitmap_create();
  for (uint32_t i = 0; i < bitmap_data_b.size(); i++) {
    roaring_bitmap_add(b, bitmap_data_b[i]);
  }

  std::vector<uint32_t> bitmap_data_c = ConsumeVecInRange(fdp, 500, 0, 1000);
  roaring_bitmap_t *c = roaring_bitmap_create();
  for (uint32_t i = 0; i < bitmap_data_c.size(); i++) {
    roaring_bitmap_add(c, bitmap_data_c[i]);
  }

  std::vector<uint32_t> bitmap_data_d = ConsumeVecInRange(fdp, 500, 0, 1000);
  roaring_bitmap_t *d = roaring_bitmap_create();
  for (uint32_t i = 0; i < bitmap_data_d.size(); i++) {
    roaring_bitmap_add(d, bitmap_data_d[i]);
  }

  roaring_bitmap_t *result = roaring_bitmap_xor_many(4, &a, &b, &c, &d);

  roaring_bitmap_free(a);
  roaring_bitmap_free(b);
  roaring_bitmap_free(c);
  roaring_bitmap_free(d);
  roaring_bitmap_free(result);

  return 0;
}