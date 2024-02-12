#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

#include "fuzzing/types/container.h"

namespace fuzzing {
namespace types {

template <typename T, bool is_array, bool is_pointer>
Container<T, is_array, is_pointer>::~Container(Container * this) {
  if (is_array) {
    delete[] this->data;
  } else if (is_pointer) {
    delete this->data;
  }
}

}  // namespace types
}  // namespace fuzzing

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t capacity = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  fuzzing::types::Container<unsigned char, false, false> container(capacity);
  const size_t length = stream.ConsumeIntegralInRange<size_t>(0, capacity);
  stream.ConsumeBytes<unsigned char>(length);
  container.~Container();
  return 0;
}