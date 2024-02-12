 #include <cstdint>
#include <string>
#include <vector>

#include "butteraugli/butteraugli.h"
#include "butteraugli/butteraugli_interface.h"
#include "butteraugli/image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> input_image(data, data + size);
  std::vector<uint8_t> original_image;
  butteraugli::Image img(input_image.data(), input_image.size());
  double distance = 0;
  butteraugli::ButteraugliInterface::ComputeDifference(
      &input_image, &original_image, &img, &distance);
  return 0;
}