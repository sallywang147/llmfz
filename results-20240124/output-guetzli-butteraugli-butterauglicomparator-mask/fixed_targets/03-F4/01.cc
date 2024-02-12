#include <stdint.h>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
#include "butteraugli/butteraugli_comparator.h"
#include "butteraugli/butteraugli_format.h"
#include "butteraugli/butteraugli_ops.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  butteraugli::ButteraugliComparator comparator;
  std::vector<uint8_t> image_a(data, data + size);
  std::vector<uint8_t> image_b(data, data + size);
  comparator.Mask(&comparator, &image_a, &image_b);
  return 0;
}