#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "roaring/roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t bitmap_size = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<uint32_t> bitmap_data(bitmap_size);
  stream.ConsumeData(bitmap_data.data(), bitmap_size * sizeof(uint32_t));

  roaring_bitmap_t* bitmap = roaring_bitmap_create();
  for (const uint32_t value : bitmap_data) {
    roaring_bitmap_add(bitmap, value);
  }

  const size_t bitmap2_size = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<uint32_t> bitmap2_data(bitmap2_size);
  stream.ConsumeData(bitmap2_data.data(), bitmap2_size * sizeof(uint32_t));

  roaring_bitmap_t* bitmap2 = roaring_bitmap_create();
  for (const uint32_t value : bitmap2_data) {
    roaring_bitmap_add(bitmap2, value);
  }

  roaring_bitmap_lazy_xor_inplace(bitmap, bitmap2);

  roaring_bitmap_free(bitmap);
  roaring_bitmap_free(bitmap2);

  return 0;
}