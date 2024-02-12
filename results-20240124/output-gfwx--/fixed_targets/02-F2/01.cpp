#include "fuzzing/datasource/datasource.hpp"
#include "fuzzing/types/container.hpp"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::datasource::Datasource ds(data, size);
  fuzzing::types::Container<unsigned char, false, false> container;
  try {
    ds.Get<fuzzing::types::Container<unsigned char, false, false> >(&container, nullptr, 0);
  } catch ( ... ) {
    ds.Get<fuzzing::types::Container<unsigned char, false, false> >(&container, nullptr, 0);
  }
  return 0;
}
}