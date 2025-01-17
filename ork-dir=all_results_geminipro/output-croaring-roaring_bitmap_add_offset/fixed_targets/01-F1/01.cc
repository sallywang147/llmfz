#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "roaring/roaring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint32_t> values;
  while (stream.remaining_bytes() > 0) {
    values.push_back(stream.ConsumeIntegral<uint32_t>());
  }

  roaring_bitmap_t* bitmap = roaring_bitmap_create();
  for (uint32_t value : values) {
    roaring_bitmap_add_offset(bitmap, value);
  }
  roaring_bitmap_free(bitmap);

  return 0;
}