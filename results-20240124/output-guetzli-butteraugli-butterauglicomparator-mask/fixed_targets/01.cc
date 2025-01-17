#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  butteraugli::ButteraugliComparator comparator;
  std::vector<uint8_t> mask_data(size);
  std::vector<float> mask_weights(size);
  memcpy(mask_data.data(), data, size);
  comparator.Mask(nullptr, &mask_data, &mask_weights);
  return 0;
}