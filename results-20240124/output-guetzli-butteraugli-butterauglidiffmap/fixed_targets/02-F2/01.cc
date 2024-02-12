#include <stdint.h>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  butteraugli::Image img;
  if (!img.FromPNG(data, size)) {
    return 0;
  }
  std::vector<uint8_t> diffmap;
  std::vector<float> diffmap_float;
  butteraugli::ButteraugliDiffmap(&diffmap, &diffmap_float, &img);
  return 0;
}