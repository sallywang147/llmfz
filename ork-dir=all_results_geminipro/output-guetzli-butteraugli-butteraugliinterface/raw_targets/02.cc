#include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> input(data, data + size);
  std::vector<uint8_t> output;
  butteraugli::Image img;
  double score;
  bool status = butteraugli::ButteraugliInterface(&input, &output, &img, &score);
  (void)status;  // TODO(robryk): Verify status.
  return 0;
}