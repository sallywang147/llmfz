#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "roaring/roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t bitmap_size = stream.ConsumeIntegral<size_t>();
  const bool allocated = stream.ConsumeBool();
  std::vector<uint32_t> bitmap_data;
  bitmap_data.reserve(bitmap_size);
  for (size_t i = 0; i < bitmap_size; ++i) {
    bitmap_data.push_back(stream.ConsumeIntegral<uint32_t>());
  }
  roaring_bitmap_t* bitmap1 =
      allocated ? roaring_bitmap_create() : roaring_bitmap_direct_from_data(
                                               bitmap_data.data(), bitmap_size);
  bitmap_data.clear();
  bitmap_data.reserve(bitmap_size);
  for (size_t i = 0; i < bitmap_size; ++i) {
    bitmap_data.push_back(stream.ConsumeIntegral<uint32_t>());
  }
  roaring_bitmap_t* bitmap2 =
      allocated ? roaring_bitmap_create() : roaring_bitmap_direct_from_data(
                                               bitmap_data.data(), bitmap_size);
  const bool lazy = stream.ConsumeBool();
  roaring_bitmap_lazy_or(bitmap1, bitmap2, lazy);
  roaring_bitmap_free(bitmap1);
  roaring_bitmap_free(bitmap2);
  return 0;
}