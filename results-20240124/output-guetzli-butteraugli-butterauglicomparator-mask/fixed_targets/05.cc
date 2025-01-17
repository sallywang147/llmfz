#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> image_a(data, data + size);
  std::vector<uint8_t> image_b(data, data + size);
  butteraugli::ButteraugliComparator comparator;
  comparator.Mask(nullptr, &image_a, &image_b);
  return 0;
}
}