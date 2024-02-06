#include "butteraugli/butteraugli_comparator.h"
#include "butteraugli/butteraugli_format.h"
#include "butteraugli/butteraugli_ops.h"
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> image_a;
  std::vector<uint8_t> image_b;
  if (!butteraugli::DecodeButteraugliImage(data, size, &image_a, &image_b)) {
    return 0;
  }

  butteraugli::ButteraugliComparator comparator;
  std::vector<uint8_t> mask;
  comparator.Mask(&image_a, &image_b, &mask);  // Fix the typo here.
  return 0;
}