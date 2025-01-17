#include <cstddef>
#include <cstdint>
#include <cstring>
#include "fuzzing/types/container.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *value = reinterpret_cast<const char *>(data);
  fuzzing::types::Container<char, false, false> container(value, size);
  container.~Container();
  return 0;
}