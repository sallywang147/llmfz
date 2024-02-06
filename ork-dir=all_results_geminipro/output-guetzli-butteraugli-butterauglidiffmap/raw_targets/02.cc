#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> rgb_a(data, data + size);
  butteraugli::Image img(rgb_a.data(), rgb_a.size(), butteraugli::PixelFormat::RGBA,
                         butteraugli::Sampling::AVERAGE);
  std::vector<float> diffmap;
  std::vector<float> diffmap_sq;
  butteraugli::ButteraugliDiffmap(&diffmap, &diffmap_sq, &img);
  return 0;
}