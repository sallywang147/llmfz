 #include <stdint.h>
#include <vector>

#include "butteraugli/butteraugli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // TODO(robryk): Use nondefault parameters.
  butteraugli::ButteraugliInterface(nullptr, nullptr, nullptr, nullptr);
  return 0;
}