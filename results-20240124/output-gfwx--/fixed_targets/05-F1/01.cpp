#include <cstddef>
#include <cstdint>
#include <cstring>
#include "fuzzing/datasource/datasource.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::datasource::Base ds(data, size);
  fuzzing::types::Container<unsigned char, false, false> container;
  try {
    ds.Get<fuzzing::types::Container<unsigned char, false, false> >(&container, nullptr, 0);
  } catch (...) {
    return 0;
  }
  return 0;
}