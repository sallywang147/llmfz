 #include <stdint.h>
#include <vector>
#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> img1(data, data + size);
  std::vector<uint8_t> img2(data, data + size);
  butteraugli::Image image1(img1.data(), img1.size(), butteraugli::Image::Format::JPEG);
  butteraugli::Image image2(img2.data(), img2.size(), butteraugli::Image::Format::JPEG);
  double distance;
  (void)butteraugli::ButteraugliInterface(&img1, &img2, &image1, &distance);
  // TODO(robryk): Verify distance if ButteraugliInterface() succeeded.
  return 0;
}