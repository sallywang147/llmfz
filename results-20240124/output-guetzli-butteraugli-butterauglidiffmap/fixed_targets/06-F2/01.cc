#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"
#include "butteraugli/butteraugli_comparison.h"
#include "butteraugli/butteraugli_format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // TODO(robryk): Use nondefault parameters.
  butteraugli::ButteraugliParams params;

  // TODO(robryk): Generate images.
  std::vector<uint8_t> img1;
  std::vector<uint8_t> img2;
  butteraugli::Image butter_img1 = butteraugli::Image(img1.data(), img1.size());
  butteraugli::Image butter_img2 = butteraugli::Image(img2.data(), img2.size());

  butteraugli::ButteraugliDiffmap(&img1, &img2, &butter_img1);
  // TODO(robryk): Verify output distance if ButteraugliDiffmap() succeeded.
  return 0;
}