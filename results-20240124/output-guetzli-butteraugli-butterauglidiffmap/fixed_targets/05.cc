#include <stdint.h>
#include <string>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // TODO(robryk): Use nondefault parameters.
  butteraugli::ButteraugliParams params;
  std::vector<uint8_t> diffmap;
  std::vector<uint8_t> diffmap_float;
  butteraugli::Image img;
  butteraugli::ButteraugliDiffmap(&diffmap, &diffmap_float, &img, params);
  return 0;
}