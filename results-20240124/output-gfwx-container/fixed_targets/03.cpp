#include <cstdint>
#include <cstddef>
#include <cstring>

#include "fuzzing/types/container.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::types::Container<unsigned char, false, false> *container =
      new fuzzing::types::Container<unsigned char, false, false>(data, size);
  delete container;
  return 0;
}
}