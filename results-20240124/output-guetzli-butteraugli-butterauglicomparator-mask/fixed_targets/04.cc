#include <stdint.h>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<float> img1(size / 2);
  std::vector<float> img2(size / 2);
  for (size_t i = 0; i < size / 2; i++) {
    img1[i] = static_cast<float>(data[i]);
    img2[i] = static_cast<float>(data[i + size / 2]);
  }

  butteraugli::ButteraugliComparator comparator;
  comparator.Mask(&comparator, &img1, &img2);
  return 0;
}