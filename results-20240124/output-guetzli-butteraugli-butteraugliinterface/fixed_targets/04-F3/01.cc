#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> img_a(data, data + size);
  std::vector<uint8_t> img_b(data, data + size);
  butteraugli::Image image_a(img_a.data(), img_a.size(),
                             butteraugli::PixelFormat::kRGB,
                             butteraugli::Sampling::kLinear);
  butteraugli::Image image_b(img_b.data(), img_b.size(),
                             butteraugli::PixelFormat::kRGB,
                             butteraugli::Sampling::kLinear);
  double score;
  // TODO(robryk): Use nondefault parameters.
  butteraugli::ButteraugliInterface(&image_a, &image_b, nullptr, &score);
  // TODO(robryk): Verify output distance if ButteraugliInterface() succeeded.
  return 0;
}