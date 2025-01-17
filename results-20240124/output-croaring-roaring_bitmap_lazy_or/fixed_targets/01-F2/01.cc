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
  roaring_bitmap_add_many(a, bitmap_data_a.size(), bitmap_data_a.data());
  roaring_bitmap_run_optimize(a);
  roaring_bitmap_shrink_to_fit(a);

  std::vector<uint32_t> bitmap_data_b = ConsumeVecInRange(fdp, 500, 0, 1000);
  roaring_bitmap_t *b = roaring_bitmap_create();
  roaring_bitmap_add_many(b, bitmap_data_b.size(), bitmap_data_b.data());
  roaring_bitmap_run_optimize(b);
  roaring_bitmap_add(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_add_checked(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_add_range(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end), fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  // add half of a to b.
  roaring_bitmap_add_many(b, bitmap_data_a.size() / 2, bitmap_data_a.data());
  roaring_bitmap_remove(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_remove_checked(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_remove_range(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end),
                fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_remove_range_closed(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end),
                      fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_maximum(b);
  roaring_bitmap_minimum(b);
  roaring_bitmap_contains(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_contains_range(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end),
                  fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));

  uint32_t element = 0;
  roaring_bitmap_select(b, fdp.ConsumeIntegralInRange<uint32_t>(0, 1000), &element);
  roaring_bitmap_lazy_or(a, b, fdp.ConsumeBool());
  roaring_bitmap_jaccard_index(a, b);
  roaring_bitmap_or_cardinality(a, b);
  roaring_bitmap_andnot_cardinality(a, b);
  roaring_bitmap_xor_cardinality(a, b);
  roaring_bitmap_rank(a, fdp.ConsumeIntegralInRange<uint32_t>(0, 5000));
  roaring_bitmap_get_size_in_bytes(a);

  roaring_bitmap_t *c = roaring_bitmap_intersect(a, b);
  roaring_bitmap_t *d = roaring_bitmap_difference(a, b);
  roaring_bitmap_t *e = roaring_bitmap_or(a, b);
  roaring_bitmap_t *f = roaring_bitmap_xor(a, b);
  roaring_bitmap_or_inplace(a, e);
  roaring_bitmap_and_inplace(a, b);
  roaring_bitmap_difference_inplace(a, c);
  roaring_bitmap_xor_inplace(a, f);

  volatile bool is_equal = (roaring_bitmap_equals(a, b));

  std::vector<uint32_t> b_as_array = {0};
  b_as_array.resize(roaring_bitmap_get_cardinality(b));
  roaring_bitmap_to_uint32_array(b, b_as_array.data());

  roaring_bitmap_is_subset(a, b);
  roaring_bitmap_is_strict_subset(a, b);
  roaring_bitmap_flip(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end), fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_flip_inplace(b, fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end),
               fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));
  roaring_bitmap_remove_run_compression(b);

  // Move/copy constructors
  roaring_bitmap_t *copied = roaring_bitmap_copy(b);
  roaring_bitmap_t *moved = roaring_bitmap_move(b);

  // Asignment operators
  b = roaring_bitmap_copy(copied);
  b = roaring_bitmap_move(moved);

  // Safe read from serialized
  std::vector<char> read_buffer = fdp.ConsumeBytes<char>(100);
  try {
    roaring_bitmap_t *read_safely =
        roaring_bitmap_read_safe(read_buffer.data(), read_buffer.size());
    // The above is guaranteed to be safe. However, read_safely is maybe
    // in an improper state and it cannot be used safely (including for
    // reserialization).
  } catch(...) {}

  // The bitmap b can be serialized and re-read.
  std::size_t expected_size_in_bytes = roaring_bitmap_size_in_bytes(b);
  std::vector<char> buffer(expected_size_in_bytes);
  std::size_t size_in_bytes = roaring_bitmap_write(b, buffer.data());
  assert(expected_size_in_bytes == size_in_bytes);
  roaring_bitmap_t *bread = roaring_bitmap_read_safe(buffer.data(), size_in_bytes);
  assert(roaring_bitmap_equals(bread, b));

  roaring_bitmap_to_string(f);

  volatile int unused = 0;

  roaring_uint32_iterator_t i = roaring_bitmap_get_iterator(a);
  for (; i != NULL; i = roaring_bitmap_iterator_next(i)) {
    unused++;
  }

  roaring_bitmap_iterator_equalorlarger(roaring_bitmap_get_iterator(b), fdp.ConsumeIntegralInRange<uint32_t>(range_start, range_end));

  roaring_bitmap_free(a);
  roaring_bitmap_free(b);
  roaring_bitmap_free(c);
  roaring_bitmap_free(d);
  roaring_bitmap_free(e);
  roaring_bitmap_free(f);
  roaring_bitmap_free(copied);
  roaring_bitmap_free(moved);
  roaring_bitmap_free(bread);

  return 0;
}