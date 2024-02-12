 #include <stdint.h>
#include "butteraugli/butteraugli.h"
#include "butteraugli/butteraugli_format.h"
#include "butteraugli/butteraugli_ops.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  butteraugli::Image img;
  if (!butteraugli::DecodePng(data, size, &img)) {
    return 0;
  }
  std::vector<uint8_t> diffmap;
  std::vector<uint8_t> mask;
  butteraugli::ButteraugliDiffmap(&diffmap, &mask, &img);
  return 0;
}