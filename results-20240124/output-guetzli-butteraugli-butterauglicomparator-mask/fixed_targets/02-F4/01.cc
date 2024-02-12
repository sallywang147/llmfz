#include <cstdint>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> img1(data, data + size);
  std::vector<uint8_t> img2(data, data + size);

  butteraugli::ButteraugliComparator comparator;
  comparator.Mask(&comparator, &img1, &img2);
  return 0;
}