 #include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  butteraugli::ButteraugliComparator comparator;
  std::vector<uint8_t> mask(size);
  std::vector<uint8_t> mask2(size);
  comparator.Mask(&comparator, &mask, &mask2);
  return 0;
}