#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // TODO(robryk): Use nondefault parameters.
  butteraugli::ButteraugliParams params;
  std::vector<uint8_t> img1(data, data + size);
  std::vector<uint8_t> img2(data, data + size);
  butteraugli::Image butter_img1(img1.data(), img1.size(), butteraugli::PixelFormat::kRGB);
  butteraugli::Image butter_img2(img2.data(), img2.size(), butteraugli::PixelFormat::kRGB);
  double distance;
  (void)butteraugli::ButteraugliInterface(&img1, &img2, &butter_img1, &distance);
  // TODO(robryk): Verify output distance if ButteraugliInterface() succeeded.
  return 0;
}