#include <stdint.h>
#include <vector>

extern "C" {
#include "butteraugli/butteraugli.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> input(data, data + size);
  std::vector<uint8_t> output;
  butteraugli::Image img;
  double score;
  bool status = butteraugli::ButteraugliInterface(&input, &output, &img, &score);
  return status ? 0 : 1;  // Return 0 if the status is true, 1 otherwise.
}