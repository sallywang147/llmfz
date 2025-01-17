#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;  // Not enough data to split into two bitmaps.
  }

  FuzzedDataProvider provider(data, size);

  // Split the input into two parts to create two bitmaps.
  size_t first_size = provider.ConsumeIntegralInRange<size_t>(1, size - 1);
  std::vector<uint8_t> first_data = provider.ConsumeBytes<uint8_t>(first_size);
  std::vector<uint8_t> second_data = provider.ConsumeRemainingBytes<uint8_t>();

  // Create two bitmaps from the data.
  roaring_bitmap_t* first_bitmap = roaring_bitmap_of_ptr(first_data.size(), first_data.data());
  roaring_bitmap_t* second_bitmap = roaring_bitmap_of_ptr(second_data.size(), second_data.data());

  // Perform the operation.
  roaring_bitmap_lazy_xor_inplace(first_bitmap, second_bitmap);

  // Clean up.
  roaring_bitmap_free(first_bitmap);
  roaring_bitmap_free(second_bitmap);

  return 0;
}