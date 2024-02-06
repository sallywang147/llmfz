#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "roaring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  roaring_bitmap_t* bitmap = roaring_bitmap_create();
  size_t offset = stream.ConsumeIntegral<size_t>();
  roaring_bitmap_add_offset(bitmap, offset);
  roaring_bitmap_free(bitmap);
  return 0;
}