 #include <cstddef>
#include <cstdint>
#include <cstring>
#include "fuzzing/types/container.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::types::Container<unsigned char, false, false> container(data, size);
  fuzzing::types::Container<unsigned char, false, false>::~Container(&container);
  return 0;
}